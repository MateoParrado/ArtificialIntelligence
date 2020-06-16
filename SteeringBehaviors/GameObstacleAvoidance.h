#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"
#include "Obstacle.h"
#include <vector>

//the gamestate in which two sprites wander about the screen using pseudorandom paths and avoid obstacles
class GameObstacleAvoidance :
	public State<SteeringManager>
{
private:
	GameObstacleAvoidance(const GameObstacleAvoidance&) = delete;
	GameObstacleAvoidance& operator=(const GameObstacleAvoidance&) = delete;

	static GameObstacleAvoidance* instance;

	GameObstacleAvoidance()
	{
		sprite = sprite1 = nullptr;
	}
public:
	SteeringSprite* sprite, * sprite1;
	std::vector<Obstacle> obs;

	static GameObstacleAvoidance* getInstance()
	{
		if (!instance) instance = new GameObstacleAvoidance();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameObstacleAvoidance() {};
};

