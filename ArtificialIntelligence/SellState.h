#pragma once

#include "State.h"
#include "Fisherman.h"

//state in which the fisherman goes to the market and sells his fish
class SellState : public State<Fisherman>
{
private:
	SellState() {}

	SellState(const SellState&) = delete;
	SellState& operator=(const SellState&) = delete;

	static SellState* instance;

public:
	static SellState* getInstance()
	{
		if (!instance) instance = new SellState();

		return instance;
	}

	virtual void enter(Fisherman* f);
	virtual void exit(Fisherman* f);
	virtual void execute(Fisherman* f);

	virtual bool onMessage(Fisherman*, const Telegram& msg)
	{
		return false;
	}

	virtual ~SellState() {}
};

#define Sell SellState::getInstance()