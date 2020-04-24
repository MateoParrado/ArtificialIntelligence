#pragma once
#include "State.h"
#include "Chef.h"

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

