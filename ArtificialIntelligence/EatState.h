#pragma once
#include "State.h"
#include "Fisherman.h"

//state in which the fisherman is eating at the restaurant
class EatState :
	public State<Fisherman>
{

private:
	EatState() {}

	EatState(const EatState&) = delete;
	EatState& operator=(const EatState&) = delete;

	static EatState* instance;

public:
	static EatState* getInstance()
	{
		if (!instance) instance = new EatState();

		return instance;
	}

	virtual void enter(Fisherman* f);
	virtual void exit(Fisherman* f);
	virtual void execute(Fisherman* f);

	virtual bool onMessage(Fisherman*, const Telegram& msg)
	{
		return false;
	}

	virtual ~EatState() {}
};

#define Eat EatState::getInstance()