#include "GamePursuit.h"

GamePursuit* GamePursuit::instance = nullptr;

void GamePursuit::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200, 0.01, 0.4, 6);
	miniSprite = new SmallSteeringSprite(300, 300, 0.01, 0.8, 10);
	sprite->enableBehaviors(PURSUE);
	sprite->setPursuitTarget(miniSprite);

	miniSprite->enableBehaviors(WANDER);
}

void GamePursuit::exit(SteeringManager* s)
{
	delete sprite;
	delete miniSprite;
}

void GamePursuit::execute(SteeringManager* s)
{
	//we need to do this because if this is the first gamestate then enter will not be called and sprite will be null
	//sprite and minisprite will always be null together
	if (!sprite) enter(s);

	sprite->draw(s->renderer);
	sprite->update();
	miniSprite->draw(s->renderer);
	miniSprite->update();
}
