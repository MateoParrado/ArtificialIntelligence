#pragma once

#include "SDL.h"
#include "Vector.h"
#include "Entity.h"

//right below base game entity, base class for all graphical entities
class Sprite : public Entity
{
protected:
	Vector pos;

public:
	Sprite(double x, double y) : Entity(""), pos(x, y)
	{


	}

	virtual void update() = 0;

	virtual void draw(SDL_Renderer* r) const = 0;

	Vector getPos() const
	{
		return pos;
	}

};