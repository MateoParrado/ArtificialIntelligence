#pragma once
#include "Vector.h"
#include <vector>
#include "Obstacle.h"
#include "Path.h"

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
	Vector seek(const Vector& target) const;

	//run away from a target
	Vector flee(const Vector& target) const;

	//go to a target and stop
	Vector arrive(const Vector& target, double decelRate) const;

	//follow a random looking path
	//rad is the radius of the wander circle
	//dist is the distance from the wander circle to the entity
	//jitter is the speed at which the target position changes
	Vector wander(Vector* target, double rad, double dist, double jitter) const;

	//same as above but also avoids any obstacle in the obs avoid array
	Vector wanderObsAvoid(Vector* target, double rad, double dist, double jitter, std::vector<Obstacle>& obsArray) const;

	//same as above but avoids walls instead of obstacles
	Vector wanderWallAvoid(Vector* target, double rad, double dist, double jitter, std::vector<Wall>& walls) const;

	//try and reach the target enemy by predicting their position and seeking towards it
	Vector pursuit(const SteeringSprite* s) const;

	//same as pursuit but with fleeing away from that point
	Vector evade(const SteeringSprite* s) const;

	//tries to put itself directly between the arrive and pursuit targets
	Vector interpose(const SteeringSprite* s1, const SteeringSprite* s2) const;

	//the sprite will try and hide from sprite s by positioning itself behind one of th eobstacles such that
	//the line of sight from s to the sprite is broken
	Vector hide(const SteeringSprite* s, std::vector<Obstacle>& obs) const;

	//will follow a path
	//node is a path node
	Vector pathFollow(Node** n) const;

	//keeps a sprite at a relative local position in regards to another sprite
	Vector offsetPursuit(const SteeringSprite* s, const Vector& v) const;
};

