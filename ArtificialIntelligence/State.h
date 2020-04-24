#pragma once
#include "Telegram.h"

//abstract base class for all states
template <class T>
class State
{
public:
	//called before first time execute is called
	virtual void enter(T*) = 0;

	//called continuously as long as state is active
	virtual void execute(T*) = 0;

	//called after last time execute is called
	virtual void exit(T*) = 0;

	//used to handle receiving a message
	virtual bool onMessage(T*, const Telegram&) = 0;

	virtual ~State() {}
};