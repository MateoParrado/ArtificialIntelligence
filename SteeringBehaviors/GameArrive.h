#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"

class GameArrive :
	public State<SteeringManager>
{
private:
	GameArrive(const GameArrive&) = delete;
	GameArrive& operator=(const GameArrive&) = delete;

	static GameArrive* instance;


	Vector seekPoint;

	GameArrive()
	{
		sprite = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;

	static GameArrive* getInstance()
	{
		if (!instance) instance = new GameArrive();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GameArrive() {};
};

