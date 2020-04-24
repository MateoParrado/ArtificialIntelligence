#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"

//the gamestate in which two sprites wander about the screen using pseudorandom paths
class GameWander :
	public State<SteeringManager>
{
private:
	GameWander(const GameWander&) = delete;
	GameWander& operator=(const GameWander&) = delete;

	static GameWander* instance;

	GameWander()
	{
		sprite = sprite1 = nullptr;
	}
public:
	SteeringSprite* sprite, *sprite1;

	static GameWander* getInstance()
	{
		if (!instance) instance = new GameWander();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameWander() {};
};

