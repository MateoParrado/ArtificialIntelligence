#include "SimpleSprite.h"

void SimpleSprite::draw(SDL_Renderer* renderer) const
{
	Vector c1 = Vector::rotate_point(pos, Vector(pos.getX(), pos.getY() - 20), angle);
	Vector c2 = Vector::rotate_point(pos, Vector(pos.getX() - 10, pos.getY() + 20), angle);
	Vector c3 = Vector::rotate_point(pos, Vector(pos.getX() + 10, pos.getY() + 20), angle);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, (int)c1.getX(), (int)c1.getY(), (int)c2.getX(), (int)c2.getY());
	SDL_RenderDrawLine(renderer, (int)c2.getX(), (int)c2.getY(), (int)c3.getX(), (int)c3.getY());
	SDL_RenderDrawLine(renderer, (int)c3.getX(), (int)c3.getY(), (int)c1.getX(), (int)c1.getY());
}

//weird warning in this code
#pragma warning( disable : 26451 )
void SimpleSprite::update()
{
	VehicleSprite::update();

	if (pos.getX() > WINDOW_WIDTH + 20)
	{
		pos.setX(-20);
	}
	else if (pos.getX() < -20)
	{
		pos.setX(WINDOW_WIDTH + 20);
	}

	if (pos.getY() > WINDOW_HEIGHT + 20)
	{
		pos.setY(-20);
	}
	else if (pos.getY() < -20)
	{
		pos.setY(WINDOW_HEIGHT + 20);
	}
}
