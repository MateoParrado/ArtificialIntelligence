#pragma once
#include <State.h>
#include "SteeringSprite.h"

class SeekState :
	public State<SteeringSprite>
{
private:
	SeekState() {}

	SeekState(const SeekState&) = delete;
	SeekState& operator=(const SeekState&) = delete;

	static SeekState* instance;

public:
	static SeekState* getInstance()
	{
		if (!instance) instance = new SeekState();

		return instance;
	}

	virtual void enter(SteeringSprite* s);
	virtual void exit(SteeringSprite* s);
	virtual void execute(SteeringSprite* s);

	virtual bool onMessage(SteeringSprite* s, const Telegram& t)
	{
		return false;
	}

	virtual ~SeekState() {}
};

#define Seek SeekState::getInstance()