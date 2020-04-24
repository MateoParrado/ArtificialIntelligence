#pragma once
#include "VehicleSprite.h"
class SimpleSprite :
	public VehicleSprite
{
public:
	SimpleSprite(double x, double y) : VehicleSprite(x, y, 1)
	{

	}

	virtual void draw(SDL_Renderer* renderer) const;

	virtual void update();

	virtual bool handleMessage(const Telegram& message)
	{
		return false;
	}

};

