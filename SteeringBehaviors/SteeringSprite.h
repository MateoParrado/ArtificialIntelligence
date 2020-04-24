#pragma once
#include "SimpleSprite.h"
#include "Steering.h"

//TODO: MAKE THE BOOLS LIKE	seek, flee and arrive a bit thing that we or together

//THIS CLASS IS DERIVED FROM:
//Entity/Sprite for abstract functionality
//VehicleSprite for physics
//SimpleSprite for graphics
//this class is an implementation of simple sprite where the behavior is controller by steering behaviors
class SteeringSprite :
	public SimpleSprite
{
private:
	Steering steer;

	//note that more than one of these can be active at once
	bool seek, flee, arrive;
	
public:
	Vector target;

	SteeringSprite(double x, double y);

	virtual void update();

	virtual bool handleMessage(const Telegram& msg)
	{
		return false;
	}

	void setTarget(const Vector& vec)
	{
		target = vec;
	}

	void seekOn() { seek = true; }
	void seekOff() { seek = false; }
	void fleeOn() { flee = true; }
	void fleeOff() { flee = false; }
	void arriveOn() { arrive = true; }
	void arriveOff() { arrive = false; }

	virtual ~SteeringSprite() 
	{
	}
};

