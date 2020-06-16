#pragma once

//this header contains both obstale classes implemented here (wall and obstacle)

#include "SDL.h"
#include "Vector.h"

//the circles that are avoided in the obstacle avoidance scene
struct Obstacle
{
public:
	Vector pos;
	double r;

	Obstacle() {}
	Obstacle(double _x, double _y, double _radius) : pos(_x, _y), r(_radius) {}

	void draw(SDL_Renderer* r);
};

//simple wall that is represented as a line segment
struct Wall
{
public:
	Vector firstPoint, secondPoint;
	Vector normal;

	Wall() {}
	Wall(double x1, double y1, double x2, double y2) : firstPoint(x1, y1), secondPoint(x2, y2) 
	{
		updateNormal();
	}
	void updateNormal();

	void draw(SDL_Renderer* r);
};