#include "Obstacle.h"

//maybe should move into a utility class if needed by other files
void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}


void Obstacle::draw(SDL_Renderer* r)
{
	DrawCircle(r, (int32_t)pos.getX(), (int32_t)pos.getY(), (int32_t)this->r);
}

void Wall::updateNormal()
{
	normal = Vector(-(firstPoint.getY() - secondPoint.getY()), firstPoint.getX() - secondPoint.getX());
}

void Wall::draw(SDL_Renderer* r)
{
	SDL_RenderDrawLine(r, (int)firstPoint.getX(), (int)firstPoint.getY(), (int)secondPoint.getX(), (int)secondPoint.getY());
}
