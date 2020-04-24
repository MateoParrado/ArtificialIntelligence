#pragma once
#include "Telegram.h"

template <class T>
class State
{
public:
	virtual void enter(T*) = 0;

	virtual void execute(T*) = 0;

	virtual void exit(T*) = 0;

	virtual bool onMessage(T*, const Telegram&) = 0;

	virtual ~State() {}
};