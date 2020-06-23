#include "GamePathFollow.h"

GamePathFollow* GamePathFollow::instance = nullptr;

void GamePathFollow::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200, 0.01, 0.3, 8);
	sprite->enableBehaviors(PATH_FOLLOW);
	sprite->setSeekTarget(Vector(300, 300));

	path = new Path();
}

void GamePathFollow::exit(SteeringManager* s)
{
	delete sprite;
	delete path;
}

void GamePathFollow::execute(SteeringManager* s)
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

	path->draw(s->renderer);
}
