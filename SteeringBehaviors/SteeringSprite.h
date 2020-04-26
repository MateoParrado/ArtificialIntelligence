#pragma once
#include "SimpleSprite.h"
#include "Steering.h"
#include "Definitions.h"

//THIS CLASS IS DERIVED FROM:
//Entity/Sprite for abstract functionality
//VehicleSprite for physics
//SimpleSprite for graphics
//this class is an implementation of simple sprite where the behavior is controller by steering behaviors
class SteeringSprite :
	public SimpleSprite
{
private:
	Steering steer = Steering(this);

	Vector seekTarget, arriveTarget, fleeTarget, wanderTarget;
	SteeringSprite* pursuitTarget, *evadeTarget;

	//used to store the boolean combination of steering behaviors that are enabled / disabled
	uint32_t enabledBehaviors;

public:
	friend class Steering;

	SteeringSprite(double x, double y);

	virtual void update();

	virtual bool handleMessage(const Telegram& msg)
	{
		return false;
	}

	//enable behaviors as defined by the macros in definitions.h
	void enableBehaviors(uint32_t b)
	{
		enabledBehaviors |= b;
	}

	void disableBehaviors(uint32_t b)
	{
		enabledBehaviors &= b;
	}

	//target setters
	void setSeekTarget(const Vector& t) { seekTarget = t; }
	void setFleeTarget(const Vector& t) { fleeTarget = t; }
	void setArriveTarget(const Vector& t) { arriveTarget = t; }
	void setWanderTarget(const Vector& t) { wanderTarget = t; }
	void setPursuitTarget(SteeringSprite* t) { pursuitTarget = t; }
	void setEvadeTarget(SteeringSprite* t) { evadeTarget = t; }

	//target getters
	const Vector& getSeekTarget() const { return seekTarget; };
	const Vector& getFleeTarget() const { return fleeTarget; };
	const Vector& getArriveTarget() const { return arriveTarget; };


	double getAngle() { return angle; }

	virtual ~SteeringSprite() 
	{
	}
};

