#include "GameSeek.h"

GameSeek* GameSeek::instance = nullptr;

void GameSeek::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite->seekOn();
}

void GameSeek::exit(SteeringManager* s)
{
	delete sprite;
}

void GameSeek::execute(SteeringManager* s)
{
	//when the game starts it doesn't call enter for us, so we need to call it ourselves to initialize our sprite
	if (!sprite) enter(s);

	//update sprite
	sprite->draw(s->renderer);
	sprite->update();

	//target rectangle
	SDL_Rect r;
	r.x = (int)sprite->getTarget().getX();
	r.y = (int)sprite->getTarget().getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
