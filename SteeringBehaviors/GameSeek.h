#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"

class GameSeek :
	public State<SteeringManager>
{
private:
	GameSeek(const GameSeek&) = delete;
	GameSeek& operator=(const GameSeek&) = delete;

	static GameSeek* instance;


	Vector seekPoint;

	GameSeek()
	{
		sprite = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;

	static GameSeek* getInstance()
	{
		if (!instance) instance = new GameSeek();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameSeek() {};
};

