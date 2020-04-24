#pragma once
#include "State.h"
#include "Fisherman.h"

class FishermanGlobalState :
	public State<Fisherman>
{
private:
	FishermanGlobalState() {}

	FishermanGlobalState(const FishermanGlobalState&) = delete;
	FishermanGlobalState& operator=(const FishermanGlobalState&) = delete;

	static FishermanGlobalState* instance;

public:
	static FishermanGlobalState* getInstance()
	{
		if (!instance) instance = new FishermanGlobalState();

		return instance;
	}

	virtual void enter(Fisherman* f);
	virtual void exit(Fisherman* f);
	virtual void execute(Fisherman* f);

	virtual bool onMessage(Fisherman*, const Telegram& msg)
	{
		return false;
	}

	virtual ~FishermanGlobalState() {}
};

#define FishermanGlobal FishermanGlobalState::getInstance()