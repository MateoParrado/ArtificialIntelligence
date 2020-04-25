#include "GameSeek.h"

GameSeek* GameSeek::instance = nullptr;

void GameSeek::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite->enableBehaviors(SEEK);
	sprite->setSeekTarget(Vector(300, 300));
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
	r.x = (int)sprite->getSeekTarget().getX();
	r.y = (int)sprite->getSeekTarget().getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
