#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"
#include "Obstacle.h"
#include <vector>

//the gamestate in which two sprites wander about the screen using pseudorandom paths avoiding walls
class GameWallAvoidance :
	public State<SteeringManager>
{
private:
	GameWallAvoidance(const GameWallAvoidance&) = delete;
	GameWallAvoidance& operator=(const GameWallAvoidance&) = delete;

	static GameWallAvoidance* instance;

	GameWallAvoidance()
	{
		sprite = sprite1 = nullptr;
	}
public:
	SteeringSprite* sprite, * sprite1;
	std::vector<Wall> walls;

	static GameWallAvoidance* getInstance()
	{
		if (!instance) instance = new GameWallAvoidance();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameWallAvoidance() {};
};

