#pragma once
#include "VehicleSprite.h"

//a vehicle sprite that draws a triangle on a renderer
class SimpleSprite :
	public VehicleSprite
{
public:
	SimpleSprite(double x, double y, double minForce, double maxForce, double maxSpeed) : VehicleSprite(x, y, 1, minForce, maxForce, maxSpeed)
	{

	}

	virtual void draw(SDL_Renderer* renderer) const;

	virtual void update();

	virtual bool handleMessage(const Telegram& message)
	{
		return false;
	}

};

