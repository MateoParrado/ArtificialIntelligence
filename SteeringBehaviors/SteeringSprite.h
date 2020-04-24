#pragma once
#include "SimpleSprite.h"
#include "StateMachine.h"


class SteeringSprite :
	public SimpleSprite
{
private:
	StateMachine<SteeringSprite>* stateMach;

public:
	Vector target;

	SteeringSprite(double x, double y);

	virtual void update()
	{
		SimpleSprite::update();

		stateMach->update();
	}

	void changeState(State<SteeringSprite>* s)
	{
		stateMach->changeState(s);
	}

	void revertState()
	{
		stateMach->revertState();
	}

	virtual bool handleMessage(const Telegram& msg)
	{
		return stateMach->handleMessage(msg);
	}

	void setTarget(const Vector& vec)
	{
		target = vec;
	}

	virtual ~SteeringSprite() 
	{
		delete stateMach;
	}
};

