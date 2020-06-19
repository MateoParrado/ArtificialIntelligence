#include "GameInterpose.h"

GameInterpose* GameInterpose::instance = nullptr;

void GameInterpose::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 20, 0.01, 1, 5);
	sprite1 = new SteeringSprite(300, 300, 0.01, 1, 5);
	sprite2 = new SmallSteeringSprite(150, 150, 0.01, .3, 5);
	sprite->enableBehaviors(WANDER);
	sprite1->enableBehaviors(WANDER);
	sprite2->enableBehaviors(INTERPOSE);
	sprite2->setPursuitTarget(sprite);
	sprite2->setEvadeTarget(sprite1);
}

void GameInterpose::exit(SteeringManager* s)
{
	delete sprite2;
	delete sprite1;
	delete sprite;
}

void GameInterpose::execute(SteeringManager* s)
{
	//when the game starts it doesn't call enter for us, so we need to call it ourselves to initialize our sprite
	//sprite and sprite1 will always either be or not be nullptr together
	if (!sprite) enter(s);

	//update sprite
	sprite->draw(s->renderer);
	sprite->update();

	sprite1->draw(s->renderer);
	sprite1->update();

	sprite2->draw(s->renderer);
	sprite2->update();
}
