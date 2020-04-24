#pragma once
#include "State.h"
#include "Chef.h"

//state in which the fisherman eats steak
//previous state will always be waiting for food state
//triggered by a message from the chef that the food is ready
class CookSteakState :
	public State<Chef>
{
private:
	CookSteakState() {}

	CookSteakState(const CookSteakState&) = delete;
	CookSteakState& operator=(const CookSteakState&) = delete;

	static CookSteakState* instance;

public:
	static CookSteakState* getInstance()
	{
		if (!instance) instance = new CookSteakState();

		return instance;
	}

	virtual void enter(Chef* f);
	virtual void exit(Chef* f);
	virtual void execute(Chef* f);

	virtual bool onMessage(Chef*, const Telegram& msg);

	virtual ~CookSteakState() {}
};

#define CookSteak CookSteakState::getInstance()

