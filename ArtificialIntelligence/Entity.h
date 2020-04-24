#pragma once
#include <string>
#include "Telegram.h"

//TODO: MOVE THE DISPLAY AND NAME PART OF ENTTITY INTO A DERIVED CLASS CALLED "TEXT ENTITY" SO THAT SPRITES DONT NEED IT


//the base class for every entity (and sprite) in the game
class Entity
{
private:
	//each enttiy has a unique id for messaging
	int id;

	//to make sure no two have the same id
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

	//function to display text as if the entity wasy saying it
	//Say name = Fisherman Marty and s = "I'm hungry"
	// Returns: "Fisherman Marty: I'm hungry"
	void display(std::string s);
};