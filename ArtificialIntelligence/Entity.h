#pragma once
#include <string>
#include "Telegram.h"

class Entity
{
private:
	int id;

	static int nextId;
	std::string name;
public:
	Entity(std::string _name) : name(_name)
	{
		id = nextId++;
	}

	virtual ~Entity() {}

	virtual void update() = 0;

	virtual bool handleMessage(const Telegram& message) = 0;

	int getId() const { return id; };

	void display(std::string s);
};