#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"
#include "Obstacle.h"
#include <vector>

//the gamestate in which two sprites wander about the screen using pseudorandom paths and avoid obstacles
class GameHide :
	public State<SteeringManager>
{
private:
	GameHide(const GameHide&) = delete;
	GameHide& operator=(const GameHide&) = delete;

	static GameHide* instance;

	GameHide()
	{
		sprite = sprite1 = nullptr;
	}
public:
	SteeringSprite* sprite, * sprite1;
	std::vector<Obstacle> obs;

	static GameHide* getInstance()
	{
		if (!instance) instance = new GameHide();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameHide() {};
};

