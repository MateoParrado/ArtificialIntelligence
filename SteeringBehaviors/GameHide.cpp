#include "GameHide.h"

GameHide* GameHide::instance = nullptr;

void GameHide::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(300, 100, 0.01, 1, 5); // try 200, 200 if you want to break it
	sprite1 = new SteeringSprite(300, 300, 0.01, 1, 5);
	sprite->enableBehaviors(WANDER_OBS_AVOID);
	sprite1->enableBehaviors(HIDE);
	sprite1->setEvadeTarget(sprite);


	for (int i = 0; i < 6; i++)
	{
		obs.push_back(Obstacle());
	}

	obs[0].pos = Vector(130, 130);
	obs[0].r = 75;

	obs[1].pos = Vector(400, 70);
	obs[1].r = 25;

	obs[2].pos = Vector(340, 250);
	obs[2].r = 45;

	obs[3].pos = Vector(290, 120);
	obs[3].r = 15;

	obs[4].pos = Vector(130, 280);
	obs[4].r = 45;

	obs[5].pos = Vector(470, 320);
	obs[5].r = 35;
}

void GameHide::exit(SteeringManager* s)
{
	delete sprite1;
	delete sprite;
}

void GameHide::execute(SteeringManager* s)
{
	//when the game starts it doesn't call enter for us, so we need to call it ourselves to initialize our sprite
	//sprite and sprite1 will always either be or not be nullptr together
	if (!sprite) enter(s);

	//update sprite
	sprite->draw(s->renderer);
	sprite->update();

	sprite1->draw(s->renderer);
	sprite1->update();

	for (int i = 0; i < 6; i++)
	{
		obs[i].draw(s->renderer);
	}
}
