#include "GameSeek.h"
#include "SteerState.h"

GameSeek* GameSeek::instance = nullptr;

void GameSeek::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite->changeState(Steer);
	//sprite->setVelocity(0.01, 0.01);
}

void GameSeek::exit(SteeringManager* s)
{
	delete sprite;
}

void GameSeek::execute(SteeringManager* s)
{
	if (!sprite) enter(s);

	sprite->draw(s->renderer);
	sprite->update();

	SDL_Rect r;
	r.x = sprite->target.getX();
	r.y = sprite->target.getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
