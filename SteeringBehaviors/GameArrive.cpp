#include "GameArrive.h"

GameArrive* GameArrive::instance = nullptr;

void GameArrive::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite->arriveOn();
}

void GameArrive::exit(SteeringManager* s)
{
	delete sprite;
}

void GameArrive::execute(SteeringManager* s)
{
	//when setting this on startup enter is not called, so we must do it ourselves if we are the first state
	if (!sprite) enter(s);

	sprite->draw(s->renderer);
	sprite->update();

	//target rect
	SDL_Rect r;
	r.x = (int)sprite->target.getX();
	r.y = (int)sprite->target.getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
