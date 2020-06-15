#include "Steering.h"
#include "Definitions.h"
#include "SteeringSprite.h"
#include "Obstacle.h"
#include <stdlib.h>
#include <vector>

//used for debugging obstacle avoidance, should be deleted
#include <iostream>
#include<Windows.h>
using namespace std;

//go from vector pos to vector target, overshooting it and them coming back
Vector Steering::seek(const Vector& target)
{
	//get vector from pos to target
	Vector temp = target - owner->pos;

	//make it the length of speed cap
	temp.normalize();
	temp *= SPEED_CAP;

	//add a force that decreases the faster we're going
	return temp - owner->velocity;
}

//start and pos and go exactly away from target
Vector Steering::flee(const Vector& target)
{
	//find vector from target to pos
	Vector temp = owner->pos - target;

	//make teh vector the length of speed cal
	temp.normalize();
	temp *= SPEED_CAP;

	//add a force that decreases the faster we're going
	return temp - owner->velocity;
}

//go from pos to target and stop without overshooting
Vector Steering::arrive(const Vector& target, double decelRate)
{
	//get vector from pos to target
	Vector temp = target - owner->pos;

	//find the distance squared between pos and target
	double dist = temp.length();

	if (dist > 0)
	{
		//this is our desired velocity, note that it decreases with distance
		double speed = dist / 10;

		//make sure we don't pass speed_cap
		speed = (speed < SPEED_CAP) ? speed : SPEED_CAP;

		//make the vector teh magnitude of speed (dividing by lenSq is normalizing)
		temp *= speed / dist;

		//add a force that decreases the faster we're going
		return temp - owner->velocity;
	}

	//if we're there then just return 0
	return Vector::Zero();
}

//weird warning, ignore it
#pragma warning ( disable: 26451)

//generates ramdon seeming movement
Vector Steering::wander(Vector* target, double rad, double dist, double jitter)
{
	//add small amount to target
	*target += Vector((static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2 - 1) * jitter,
		(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2 - 1) * jitter);

	//project it back on the unit circle
	target->normalize();

	//multiply it by the desired radius
	*target *= rad;

	//offset it
	Vector localTarget = *target + Vector(0, -dist) + owner->pos;

	//put it in world coordinates
	localTarget = Vector::rotate_point(owner->pos, localTarget, owner->angle);

	return localTarget - owner->pos;
}

Vector Steering::wanderObsAvoid(Vector* target, double rad, double dist, double jitter, std::vector<Obstacle>& obsArray)
{
	//get the length of teh box we are using to check for collisions
	double boxLength = MIN_BOX_LENGTH + (owner->getVelocity().length() / SPEED_CAP) * MIN_BOX_LENGTH;

	//filter out any obstacles too far away to collide with the box (as well as doing all our other filtering steps for efficiency)
	std::vector<Obstacle> obs;
	for (int i = 0; i < obsArray.size(); i++)
	{
		if (owner->pos.distance(obsArray[i].pos) < boxLength + obsArray[i].r)
		{

			//convert the obstacles to local coordinates
			Obstacle o;
			o.r = obsArray[i].r;
			o.pos = owner->pos.worldToLocal(obsArray[i].pos, owner->angle);

			//only keep the obstacles if their local y is positive
			if (o.pos.getY() <= 0)
			{
				continue;
			}

			//if the local position is negative, check if when we add the radius and half the box width is it positive
			//if it is then we consider it
			//15 is half the bounding box
			if (o.pos.getX() <= 0 && o.pos.getX() + o.r + 15 >= 0)
				obs.push_back(o);

			//same thing for other sign
			else if (o.pos.getX() >= 0 && o.pos.getX() - o.r - 15 <= 0)
				obs.push_back(o);

		}
	}

	if (obs.size() > 0)
	{

		double closestDist = 10000000;
		int closestIndex = -1;

		//we will now find the intersection point of of the line and our current trajectory
		//we know the x coordinate will be zero, so we can solve the equation (x-c_x)^2+(y-c_y)^2=r^2 with x = 0
		//obs[i].pos.getX()^2+(y-obs[i].pos.getY())^2 = (obs[i].r+15)^2
		//y-obs[i].pos.getY() = sqrt((obs[i].r+15)^2 - obs[i].pos.getX()^2)
		//y = sqrt((obs[i].r+15)^2 - obs[i].pos.getX()^2) + obs[i].pos.getY()
		
		for (int i = 0; i < obs.size(); i++)
		{
			double temp = sqrt((obs[i].r + 15)* (obs[i].r + 15) - obs[i].pos.getX() * obs[i].pos.getX()); //only calculate sqrt once
			double first = temp + obs[i].pos.getY();
			double second = -temp + obs[i].pos.getY();

			double absolute = 0;

			//if either are less than zero do the other one, else choose the min
			if (first < 0)
				absolute = second;
			else if (second < 0)
				absolute = first;
			else
				absolute = first < second ? first : second;

			if (absolute < closestDist)
			{
				closestDist = absolute;
				closestIndex = i;
			}
		}

		//calculate steering force based on closest dist

		//the closer the obstacle the stronger the steering force
		double mult = 1.0 + ((boxLength - obs[closestIndex].pos.getX()) / boxLength);
		mult /= 100;

		Vector force = Vector::Zero();

		force.setX((obs[closestIndex].r - obs[closestIndex].pos.getX()) * mult);

		//this is the braking force, also proportional to dist
		force.setY((obs[closestIndex].r - obs[closestIndex].pos.getY()) * 0.02);

		return Vector::Zero().localToWorld(force, owner->angle);
	}

	return wander(target, rad, dist, jitter);
	//return Vector(1, 0);
}

Vector Steering::pursuit(const SteeringSprite* s)
{
	//if we aren't moving then start moving so we have a real heading
	if (!owner->velocity.lengthSq())
	{
		return seek(s->pos);
	}

	//first find the vector from us to the other sprite
	Vector toSprite = s->pos - owner->pos;

	//find the angle between us and them
	double relativeHeading = (owner->velocity).heading().dot((s->velocity).heading());

	//if we are looking at them then just seek at them
	if (toSprite.dot((owner->velocity).heading()) > 0 && //are we facing the right direction
		relativeHeading < -0.95) //are we within 18 degrees of them
	{
		return seek(s->pos);
	}

	//the greater the distance the greater the look ahead time, and the greater the velocities the less the lookahead time
	double lookAheadTime = toSprite.length() / ((owner->velocity).length() + (s->velocity).length());

	return seek(s->pos + s->velocity * lookAheadTime);
}

Vector Steering::evade(const SteeringSprite* s)
{
	//if we aren't moving then start moving so we have a real heading
	if (!owner->velocity.lengthSq())
	{
		return flee(s->pos);
	}

	//first find the vector from us to the other sprite
	Vector toSprite = s->pos - owner->pos;

	//find the angle between us and them
	double relativeHeading = (owner->velocity).heading().dot((s->velocity).heading());

	//the greater the distance the greater the look ahead time, and the greater the velocities the less the lookahead time
	double lookAheadTime = toSprite.length() / ((owner->velocity).length() + (s->velocity).length());

	return flee(s->pos + s->velocity * lookAheadTime);
}
