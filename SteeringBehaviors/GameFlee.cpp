#include "GameFlee.h"
#include "FleeState.h"

GameFlee* GameFlee::instance = nullptr;

void GameFlee::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite->changeState(Flee);
	//sprite->setVelocity(0.01, 0.01);
}

void GameFlee::exit(SteeringManager* s)
{
	delete sprite;
}

void GameFlee::execute(SteeringManager* s)
{
	if (!sprite) enter(s);

	sprite->draw(s->renderer);
	sprite->update();

	SDL_Rect r;
	r.x = (int)sprite->target.getX();
	r.y = (int)sprite->target.getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
