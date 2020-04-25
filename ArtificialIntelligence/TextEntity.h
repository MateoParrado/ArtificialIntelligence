#pragma once
#include "Entity.h"
#include <string>

//used to handle purely textual entities such as fisherman marty
class TextEntity :
	public Entity
{
private:
	std::string name;

public:
	TextEntity(std::string name) : Entity(), name(name) {}

	//function to display text as if the entity wasy saying it
	//Say name = Fisherman Marty and s = "I'm hungry"
	// Returns: "Fisherman Marty: I'm hungry"
	void display(std::string s);
};
