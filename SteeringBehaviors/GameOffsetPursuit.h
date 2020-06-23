#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"
#include "SmallSteeringSprite.h"

//the gamestate in which we have one sprite that is seeking a point changed by clicking on the screen, and arriving and stopping at it
class GameOffsetPursuit :
	public State<SteeringManager>
{
private:
	GameOffsetPursuit(const GameOffsetPursuit&) = delete;
	GameOffsetPursuit& operator=(const GameOffsetPursuit&) = delete;

	static GameOffsetPursuit* instance;

	Vector seekPoint;

	GameOffsetPursuit()
	{
		sprite = smallSprite1 = smallSprite2 = smallSprite3 = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;
	SmallSteeringSprite* smallSprite1, *smallSprite2, *smallSprite3;

	static GameOffsetPursuit* getInstance()
	{
		if (!instance) instance = new GameOffsetPursuit();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameOffsetPursuit() {};
};

