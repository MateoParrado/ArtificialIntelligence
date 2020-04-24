#pragma once
#include <State.h>
#include "SteeringSprite.h"

class FleeState :
	public State<SteeringSprite>
{
private:
	FleeState() {}

	FleeState(const FleeState&) = delete;
	FleeState& operator=(const FleeState&) = delete;

	static FleeState* instance;

public:
	static FleeState* getInstance()
	{
		if (!instance) instance = new FleeState();

		return instance;
	}

	virtual void enter(SteeringSprite* s);
	virtual void exit(SteeringSprite* s);
	virtual void execute(SteeringSprite* s);

	virtual bool onMessage(SteeringSprite* s, const Telegram& t)
	{
		return false;
	}

	virtual ~FleeState() {}
};

#define Flee FleeState::getInstance()