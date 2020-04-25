#include "Steering.h"
#include "Definitions.h"
#include "SteeringSprite.h"
#include <stdlib.h>

//go from vector pos to vector target, overshooting it and them coming back
Vector Steering::seek()
{
	//get vector from pos to target
	Vector temp = owner->target - owner->pos;

	//make it the length of speed cap
	temp.normalize();
	temp *= SPEED_CAP;
	
	//add a force that decreases the faster we're going
	return temp - owner->velocity;
}

//start and pos and go exactly away from target
Vector Steering::flee()
{
	//find vector from target to pos
	Vector temp = owner->pos - owner->target;

	//make teh vector the length of speed cal
	temp.normalize();
	temp *= SPEED_CAP;

	//add a force that decreases the faster we're going
	return temp - owner->velocity;
}

//go from pos to target and stop without overshooting
Vector Steering::arrive(double decelRate)
{
	//get vector from pos to target
	Vector temp = owner->target - owner->pos;

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

//generates ramdon seeming movement
Vector Steering::wander(double rad, double dist, double jitter)
{
	//add small amount to target
	owner->target += Vector((static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2 - 1) * jitter,
						   (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2 - 1) * jitter);

	//project it back on the unit circle
	owner->target.normalize();

	//multiply it by the desired radius
	owner->target *= rad;

	//offset it
	Vector localTarget = owner->target + Vector(0, -dist) + owner->pos;

	//put it in world coordinates
	localTarget = Vector::rotate_point(owner->pos, localTarget, owner->angle);
	(owner->testVec) = localTarget;

	return localTarget - owner->pos;
}
