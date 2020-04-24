#include "Steering.h"
#include "Definitions.h"

//go from vector pos to vector target, overshooting it and them coming back
Vector Steering::seek(Vector target, Vector pos, Vector vel)
{
	//get vector from pos to target
	Vector temp = target - pos;

	//make it the length of speed cap
	temp.normalize();
	temp *= SPEED_CAP;
	
	//add a force that decreases the faster we're going
	return temp - vel;
}

//start and pos and go exactly away from target
Vector Steering::flee(Vector target, Vector pos, Vector vel)
{
	//find vector from target to pos
	Vector temp = pos - target;

	//make teh vector the length of speed cal
	temp.normalize();
	temp *= SPEED_CAP;

	//add a force that decreases the faster we're going
	return temp - vel;
}

//go from pos to target and stop without overshooting
Vector Steering::arrive(Vector target, Vector pos, Vector vel, double decelRate)
{
	//get vector from pos to target
	Vector temp = target - pos;

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
		return temp - vel;
	}

	//if we're there then just return 0
	return Vector::Zero();
}