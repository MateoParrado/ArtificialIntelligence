#pragma once
#include "Vector.h"

class SteeringSprite;

//class to store all steering behaviors
//each steering sprite has an instance
//functions return a force, so they can be added together
class Steering
{
private:
	SteeringSprite* owner;
public:
	Steering(SteeringSprite* _owner) :owner(_owner) {};

	//to towards a target without slowing (passes through)
	Vector seek(const Vector& target);

	//run away from a target
	Vector flee(const Vector& target);

	//go to a target and stop
	Vector arrive(const Vector& target, double decelRate);

	//follow a random looking path
	//rad is the radius of the wander circle
	//dist is the distance from the wander circle to the entity
	//jitter is the speed at which the target position changes
	//test vec is unneccessary, but used to display the target point in the graphics
	Vector wander(Vector* target, double rad, double dist, double jitter);

	//try and reach the target enemy by predicting their position and seeking towards it
	Vector pursuit(const SteeringSprite* s);
};

