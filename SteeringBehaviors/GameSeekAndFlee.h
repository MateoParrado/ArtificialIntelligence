#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"

//the gamestate in which we have one sprite that is seeking a point changed by clicking on the screen
class GameSeekAndFlee :
	public State<SteeringManager>
{
private:
	GameSeekAndFlee(const GameSeekAndFlee&) = delete;
	GameSeekAndFlee& operator=(const GameSeekAndFlee&) = delete;

	static GameSeekAndFlee* instance;

	Vector seekPoint;

	GameSeekAndFlee()
	{
		sprite = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;

	static GameSeekAndFlee* getInstance()
	{
		if (!instance) instance = new GameSeekAndFlee();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameSeekAndFlee() {};
};

