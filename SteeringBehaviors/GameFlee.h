#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"

//the gamestate in which we have one sprite that is fleeing a point and going as far away from it as possible that is controlled by mouse clicks
class GameFlee :
	public State<SteeringManager>
{
private:
	GameFlee(const GameFlee&) = delete;
	GameFlee& operator=(const GameFlee&) = delete;

	static GameFlee* instance;


	Vector seekPoint;

	GameFlee()
	{
		sprite = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;

	static GameFlee* getInstance()
	{
		if (!instance) instance = new GameFlee();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameFlee() {};
};

