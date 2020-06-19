#pragma once
#include "Vector.h"
#include <vector>
#include "Obstacle.h"

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
	Vector wander(Vector* target, double rad, double dist, double jitter);

	//same as above but also avoids any obstacle in the obs avoid array
	Vector wanderObsAvoid(Vector* target, double rad, double dist, double jitter, std::vector<Obstacle>& obsArray);

	//same as above but avoids walls instead of obstacles
	Vector wanderWallAvoid(Vector* target, double rad, double dist, double jitter, std::vector<Wall>& walls);

	//try and reach the target enemy by predicting their position and seeking towards it
	Vector pursuit(const SteeringSprite* s);

	//same as pursuit but with fleeing away from that point
	Vector evade(const SteeringSprite* s);

	//tries to put itself directly between the arrive and pursuit targets
	Vector interpose(const SteeringSprite* s1, const SteeringSprite* s2);
};

