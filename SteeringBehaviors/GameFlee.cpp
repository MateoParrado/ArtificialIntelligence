#include "GameFlee.h"

GameFlee* GameFlee::instance = nullptr;

void GameFlee::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite->fleeOn();
}

void GameFlee::exit(SteeringManager* s)
{
	delete sprite;
}

void GameFlee::execute(SteeringManager* s)
{
	//we need to do this because if this is the first gamestate then enter will not be called and sprite will be null
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
