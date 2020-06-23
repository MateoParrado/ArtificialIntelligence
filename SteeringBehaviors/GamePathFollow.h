#pragma once
#include <State.h>
#include "SteeringManager.h"
#include "SteeringSprite.h"
#include "Path.h"

//the gamestate in which a sprite follows a path that is extended by clicking your mouse
class GamePathFollow :
	public State<SteeringManager>
{
private:
	GamePathFollow(const GamePathFollow&) = delete;
	GamePathFollow& operator=(const GamePathFollow&) = delete;

	static GamePathFollow* instance;

	Vector seekPoint;

	GamePathFollow()
	{
		sprite = nullptr;
		seekPoint = Vector(300, 300);
	}
public:
	SteeringSprite* sprite;
	Path* path;

	static GamePathFollow* getInstance()
	{
		if (!instance) instance = new GamePathFollow();

		return instance;
	}

	virtual void enter(SteeringManager* s);
	virtual void exit(SteeringManager* s);
	virtual void execute(SteeringManager* s);

	virtual bool onMessage(SteeringManager* s, const Telegram& msg)
	{
		return false;
	}

	virtual ~GamePathFollow() {};
};

