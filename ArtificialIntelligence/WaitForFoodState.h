#pragma once
#include "State.h"
#include "Fisherman.h"

//state when fisherman has ordered a steak and is waiting for it to be ready
class WaitForFoodState :
	public State<Fisherman>
{

private:
	WaitForFoodState() {}

	WaitForFoodState(const WaitForFoodState&) = delete;
	WaitForFoodState& operator=(const WaitForFoodState&) = delete;

	static WaitForFoodState* instance;

public:
	static WaitForFoodState* getInstance()
	{
		if (!instance) instance = new WaitForFoodState();

		return instance;
	}

	virtual void enter(Fisherman* f);
	virtual void exit(Fisherman* f);
	virtual void execute(Fisherman* f);

	virtual bool onMessage(Fisherman*, const Telegram& msg);

	virtual ~WaitForFoodState() {}
};

#define WaitForFood WaitForFoodState::getInstance()

