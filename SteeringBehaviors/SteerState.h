#pragma once
#include <State.h>
#include "SteeringSprite.h"

class SteerState :
	public State<SteeringSprite>
{
private:
	SteerState() {}

	SteerState(const SteerState&) = delete;
	SteerState& operator=(const SteerState&) = delete;

	static SteerState* instance;

public:
	static SteerState* getInstance()
	{
		if (!instance) instance = new SteerState();

		return instance;
	}

	virtual void enter(SteeringSprite* s);
	virtual void exit(SteeringSprite* s);
	virtual void execute(SteeringSprite* s);

	virtual bool onMessage(SteeringSprite* s, const Telegram& t)
	{
		return false;
	}

	virtual ~SteerState() {}
};

#define Steer SteerState::getInstance()