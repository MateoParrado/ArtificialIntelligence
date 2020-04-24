#pragma once
#include "State.h"
#include "Fisherman.h"

//a blip state in which the fisherman stops what he's doing and drinks
class DrinkState :
	public State<Fisherman>
{
private:
	DrinkState() {}

	DrinkState(const DrinkState&) = delete;
	DrinkState& operator=(const DrinkState&) = delete;

	static DrinkState* instance;

public:
	static DrinkState* getInstance()
	{
		if (!instance) instance = new DrinkState();

		return instance;
	}

	virtual void enter(Fisherman* f);
	virtual void exit(Fisherman* f);
	virtual void execute(Fisherman* f);

	virtual bool onMessage(Fisherman*, const Telegram& msg)
	{
		return false;
	}

	virtual ~DrinkState() {}
};

#define Drink DrinkState::getInstance()