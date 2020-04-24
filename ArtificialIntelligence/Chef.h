#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "State.h"
#include <string>

class Chef :
	public Entity
{
private:
	StateMachine<Chef>* stateMach;

public:
	Chef(std::string s);

	virtual void update()
	{
		stateMach->update();
	}

	void changeState(State<Chef>* s)
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

	virtual ~Chef() 
	{
		delete stateMach;
	}
};

