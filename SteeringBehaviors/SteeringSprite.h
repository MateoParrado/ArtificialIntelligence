#pragma once
#include "SimpleSprite.h"
#include "Steering.h"

class SteeringSprite :
	public SimpleSprite
{
private:
	Steering steer;

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

