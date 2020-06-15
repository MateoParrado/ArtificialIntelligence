#include "GameEvade.h"

GameEvade* GameEvade::instance = nullptr;

void GameEvade::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200, 0.01, 0.4, 8);
	miniSprite = new SmallSteeringSprite(300, 300, 0.01, 0.1, 10);
	sprite->enableBehaviors(WANDER);

	miniSprite->enableBehaviors(EVADE);
	miniSprite->setEvadeTarget(sprite);
}

void GameEvade::exit(SteeringManager* s)
{
	delete sprite;
	delete miniSprite;
}

void GameEvade::execute(SteeringManager* s)
{
	//we need to do this because if this is the first gamestate then enter will not be called and sprite will be null
	//sprite and minisprite will always be null together
	if (!sprite) enter(s);

	sprite->draw(s->renderer);
	sprite->update();
	miniSprite->draw(s->renderer);
	miniSprite->update();
}
