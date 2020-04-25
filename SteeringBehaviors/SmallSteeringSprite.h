#pragma once
#include "SteeringSprite.h"

//the same as steering sprite but with a smaller drawn triangle, purely graphical difference
class SmallSteeringSprite :
	public SteeringSprite
{
public:
	SmallSteeringSprite(double x, double y) : SteeringSprite(x, y) {}

	virtual void draw(SDL_Renderer* r);
};

