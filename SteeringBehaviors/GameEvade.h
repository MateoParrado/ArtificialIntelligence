#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SmallSteeringSprite.h"

//the gamestate in which we have one sprite that is fleeing a point and going as far away from it as possible that is controlled by mouse clicks
class GameEvade :
	public State<SteeringManager>
{
private:
	GameEvade(const GameEvade&) = delete;
	GameEvade& operator=(const GameEvade&) = delete;

	static GameEvade* instance;

	Vector seekPoint;

	GameEvade()
	{
		sprite = miniSprite = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;
	SmallSteeringSprite* miniSprite;

	static GameEvade* getInstance()
	{
		if (!instance) instance = new GameEvade();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameEvade() {};
};

