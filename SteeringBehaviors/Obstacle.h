#pragma once
#include "SDL.h"
#include "Vector.h"

struct Obstacle
{
public:
	Vector pos;
	double r;

	Obstacle() {}
	Obstacle(double _x, double _y, double _radius) : pos(_x, _y), r(_radius) {}

	void draw(SDL_Renderer* r);
};

