#include "SmallSteeringSprite.h"

void SmallSteeringSprite::draw(SDL_Renderer* renderer)
{
	//handle the rotation
	Vector c1 = Vector::rotate_point(pos, Vector(pos.getX(), pos.getY() - 10), angle);
	Vector c2 = Vector::rotate_point(pos, Vector(pos.getX() - 5, pos.getY() + 10), angle);
	Vector c3 = Vector::rotate_point(pos, Vector(pos.getX() + 5, pos.getY() + 10), angle);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, (int)c1.getX(), (int)c1.getY(), (int)c2.getX(), (int)c2.getY());
	SDL_RenderDrawLine(renderer, (int)c2.getX(), (int)c2.getY(), (int)c3.getX(), (int)c3.getY());
	SDL_RenderDrawLine(renderer, (int)c3.getX(), (int)c3.getY(), (int)c1.getX(), (int)c1.getY());
}
