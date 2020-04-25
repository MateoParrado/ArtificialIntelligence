#pragma once
#include "Telegram.h"

//the base class for every entity (and sprite) in the game
class Entity
{
private:
	//each enttiy has a unique id for messaging
	int id;

	//to make sure no two have the same id
	static int nextId;

public:
	Entity()
	{
		id = nextId++;
	}

	virtual ~Entity() {}

	virtual void update() = 0;

	virtual bool handleMessage(const Telegram& message) = 0;

	int getId() const { return id; };

};