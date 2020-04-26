#include "Steering.h"
#include "Definitions.h"
#include "SteeringSprite.h"
#include <stdlib.h>

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
