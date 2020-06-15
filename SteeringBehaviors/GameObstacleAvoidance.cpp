#include "GameObstacleAvoidance.h"

GameObstacleAvoidance* GameObstacleAvoidance::instance = nullptr;

void GameObstacleAvoidance::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(300, 100, 0.01, 1, 5); // try 200, 200 if you want to break it
	sprite1 = new SteeringSprite(300, 300, 0.01, 1, 5);
	sprite->enableBehaviors(WANDER_OBS_AVOID);
	sprite1->enableBehaviors(WANDER_OBS_AVOID);

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

void GameObstacleAvoidance::exit(SteeringManager* s)
{
	delete sprite1;
	delete sprite;
}

void GameObstacleAvoidance::execute(SteeringManager* s)
{
	//when the game starts it doesn't call enter for us, so we need to call it ourselves to initialize our sprite
	//sprite and sprite1 will always either be or not be nullptr together
	if (!sprite) enter(s);

	//update sprite
	sprite->draw(s->renderer);
	sprite->update();

	double boxLength = MIN_BOX_LENGTH + (sprite->getVelocity().length() / sprite->maxSpeed) * MIN_BOX_LENGTH;

	Vector c1 = Vector::rotate_point(sprite->getPos(), Vector(sprite->getPos().getX() + 15, sprite->getPos().getY()), sprite->getAngle());
	Vector c2 = Vector::rotate_point(sprite->getPos(), Vector(sprite->getPos().getX() - 15, sprite->getPos().getY()), sprite->getAngle());
	Vector c3 = Vector::rotate_point(sprite->getPos(), Vector(sprite->getPos().getX() + 15, sprite->getPos().getY() - boxLength), sprite->getAngle());
	Vector c4 = Vector::rotate_point(sprite->getPos(), Vector(sprite->getPos().getX() - 15, sprite->getPos().getY() - boxLength), sprite->getAngle());

	SDL_RenderDrawLine(s->renderer, c1.getX(), c1.getY(), c2.getX(), c2.getY());
	SDL_RenderDrawLine(s->renderer, c1.getX(), c1.getY(), c3.getX(), c3.getY());
	SDL_RenderDrawLine(s->renderer, c4.getX(), c4.getY(), c2.getX(), c2.getY());
	SDL_RenderDrawLine(s->renderer, c4.getX(), c4.getY(), c3.getX(), c3.getY());
	
	sprite1->draw(s->renderer);
	sprite1->update();

	boxLength = MIN_BOX_LENGTH + (sprite1->getVelocity().length() / sprite1->maxSpeed) * MIN_BOX_LENGTH;

	c1 = Vector::rotate_point(sprite1->getPos(), Vector(sprite1->getPos().getX() + 15, sprite1->getPos().getY()), sprite1->getAngle());
	c2 = Vector::rotate_point(sprite1->getPos(), Vector(sprite1->getPos().getX() - 15, sprite1->getPos().getY()), sprite1->getAngle());
	c3 = Vector::rotate_point(sprite1->getPos(), Vector(sprite1->getPos().getX() + 15, sprite1->getPos().getY() - boxLength), sprite1->getAngle());
	c4 = Vector::rotate_point(sprite1->getPos(), Vector(sprite1->getPos().getX() - 15, sprite1->getPos().getY() - boxLength), sprite1->getAngle());

	SDL_RenderDrawLine(s->renderer, c1.getX(), c1.getY(), c2.getX(), c2.getY());
	SDL_RenderDrawLine(s->renderer, c1.getX(), c1.getY(), c3.getX(), c3.getY());
	SDL_RenderDrawLine(s->renderer, c4.getX(), c4.getY(), c2.getX(), c2.getY());
	SDL_RenderDrawLine(s->renderer, c4.getX(), c4.getY(), c3.getX(), c3.getY());

	for (int i = 0; i < 6; i++)
	{
		obs[i].draw(s->renderer);
	}
}
