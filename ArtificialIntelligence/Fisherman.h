#pragma once
#include "Enums.h"
#include "TextEntity.h"
#include "StateMachine.h"
#include "State.h"
#include <string>

//Possible local states: eat, drink (blip state), fishing, sell, waitforfood (when waiting for a message from the chef)
//Possible global states: fisherman global state
class Fisherman : public TextEntity
{
private:
	Location location = Location::MARKET;

	StateMachine<Fisherman>* stateMach;
public:
	int thirst = 0; //the higher the value the more thirsty he is
	int hunger = 0; //the higher the hunger the more thirsty he is
	int fish = 0;
	int money = 0;

	Fisherman(std::string s);

	virtual void update()
	{
		hunger++;
		thirst++;
		stateMach->update();
	}

	Location getLocation() const { return location; };

	void setLocation(Location l) { location = l; };

	void changeState(State<Fisherman>* s)
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

	virtual ~Fisherman() 
	{
		delete stateMach;
	}
};

