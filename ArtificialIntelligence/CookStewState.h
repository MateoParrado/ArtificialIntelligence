#pragma once
#include "State.h"
#include "Chef.h"

//the state in which the chef cooks stew, which he is doing constantly unless prompted by a message from the fisherman
class CookStewState :
	public State<Chef>
{
private:
	CookStewState() {}

	CookStewState(const CookStewState&) = delete;
	CookStewState& operator=(const CookStewState&) = delete;

	static CookStewState* instance;

public:
	static CookStewState* getInstance()
	{
		if (!instance) instance = new CookStewState();

		return instance;
	}

	virtual void enter(Chef* f);
	virtual void exit(Chef* f);
	virtual void execute(Chef* f);

	virtual bool onMessage(Chef*, const Telegram& msg);

	virtual ~CookStewState() {}
};

#define CookStew CookStewState::getInstance()