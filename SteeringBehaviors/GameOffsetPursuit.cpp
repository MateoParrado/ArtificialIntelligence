#include "GameOffsetPursuit.h"

GameOffsetPursuit* GameOffsetPursuit::instance = nullptr;

void GameOffsetPursuit::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200, 0.01, 0.3, 5);
	sprite->enableBehaviors(ARRIVE);
	sprite->setArriveTarget(Vector(300, 300));

	smallSprite1 = new SmallSteeringSprite(300, 300, 0.01, 0.3, 5);
	smallSprite2 = new SmallSteeringSprite(300, 300, 0.01, 0.3, 5);
	smallSprite3 = new SmallSteeringSprite(300, 300, 0.01, 0.3, 5);

	smallSprite1->enableBehaviors(OFFSET_PURSUIT);
	smallSprite2->enableBehaviors(OFFSET_PURSUIT);
	smallSprite3->enableBehaviors(OFFSET_PURSUIT);

	smallSprite1->setOffset(Vector(20, 0));
	smallSprite2->setOffset(Vector(0, -80));
	smallSprite3->setOffset(Vector(-20, 0));

	smallSprite1->setPursuitTarget(sprite);
	smallSprite2->setPursuitTarget(sprite);
	smallSprite3->setPursuitTarget(sprite);
}

void GameOffsetPursuit::exit(SteeringManager* s)
{
	delete sprite;
	delete smallSprite1;
	delete smallSprite2;
	delete smallSprite3;
}

void GameOffsetPursuit::execute(SteeringManager* s)
{
	//when setting this on startup enter is not called, so we must do it ourselves if we are the first state
	if (!sprite) enter(s);

	sprite->draw(s->renderer);
	sprite->update();

	smallSprite1->draw(s->renderer);
	smallSprite1->update();

	smallSprite2->draw(s->renderer);
	smallSprite2->update();

	smallSprite3->draw(s->renderer);
	smallSprite3->update();

	//target rect
	SDL_Rect r;
	r.x = (int)sprite->getArriveTarget().getX();
	r.y = (int)sprite->getArriveTarget().getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
