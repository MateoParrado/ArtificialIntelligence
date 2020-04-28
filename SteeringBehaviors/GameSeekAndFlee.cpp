#include "GameSeekAndFlee.h"

GameSeekAndFlee* GameSeekAndFlee::instance = nullptr;

void GameSeekAndFlee::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite->enableBehaviors(SEEK);
	sprite->enableBehaviors(FLEE);
	sprite->setSeekTarget(Vector(300, 300));
	sprite->setFleeTarget(Vector(100, 100));
}

void GameSeekAndFlee::exit(SteeringManager* s)
{
	delete sprite;
}

void GameSeekAndFlee::execute(SteeringManager* s)
{
	//when the game starts it doesn't call enter for us, so we need to call it ourselves to initialize our sprite
	if (!sprite) enter(s);

	//update sprite
	sprite->draw(s->renderer);
	sprite->update();

	//seek target rectangle
	SDL_Rect r;
	r.x = (int)sprite->getSeekTarget().getX();
	r.y = (int)sprite->getSeekTarget().getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);

	SDL_SetRenderDrawColor(s->renderer, 255, 0, 0, 255);

	//flee target rectangle
	r.x = (int)sprite->getFleeTarget().getX();
	r.y = (int)sprite->getFleeTarget().getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
