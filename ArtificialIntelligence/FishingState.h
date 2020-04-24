#pragma once
#include "State.h"
#include "Fisherman.h"

class FishingState : public State<Fisherman>
{
private:
	FishingState() {}

	FishingState(const FishingState&) = delete;
	FishingState& operator=(const FishingState&) = delete;

	static FishingState* instance;

public:
	static FishingState* getInstance()
	{
		if (!instance) instance = new FishingState();

		return instance;
	}

	virtual void enter(Fisherman* f);
	virtual void exit(Fisherman* f);
	virtual void execute(Fisherman* f);

	virtual bool onMessage(Fisherman*, const Telegram& msg)
	{
		return false;
	}

	virtual ~FishingState() {}
};

#define Fish FishingState::getInstance()