#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"
#include "SmallSteeringSprite.h"

//the gamestate in which two sprites wander about the screen using pseudorandom paths
//and one sprite will try and interpose itself between them
class GameInterpose :
	public State<SteeringManager>
{
private:
	GameInterpose(const GameInterpose&) = delete;
	GameInterpose& operator=(const GameInterpose&) = delete;

	static GameInterpose* instance;

	GameInterpose()
	{
		sprite = sprite1 = sprite2 = nullptr;
	}
public:
	SteeringSprite* sprite, * sprite1; 
	SmallSteeringSprite* sprite2;

	static GameInterpose* getInstance()
	{
		if (!instance) instance = new GameInterpose();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameInterpose() {};
};

