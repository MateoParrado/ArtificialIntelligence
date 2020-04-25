#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SmallSteeringSprite.h"

//the gamestate in which we have one sprite that is fleeing a point and going as far away from it as possible that is controlled by mouse clicks
class GamePursuit :
	public State<SteeringManager>
{
private:
	GamePursuit(const GamePursuit&) = delete;
	GamePursuit& operator=(const GamePursuit&) = delete;

	static GamePursuit* instance;

	Vector seekPoint;

	GamePursuit()
	{
		sprite = miniSprite = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;
	SmallSteeringSprite* miniSprite;

	static GamePursuit* getInstance()
	{
		if (!instance) instance = new GamePursuit();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GamePursuit() {};
};

