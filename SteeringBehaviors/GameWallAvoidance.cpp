#include "GameWallAvoidance.h"

GameWallAvoidance* GameWallAvoidance::instance = nullptr;

void GameWallAvoidance::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(300, 100, 0.01, 1, 5); // try 200, 200 if you want to break it
	sprite1 = new SteeringSprite(300, 300, 0.01, 1, 5);
	sprite->enableBehaviors(WANDER_WALL_AVOID);
	sprite1->enableBehaviors(WANDER_WALL_AVOID);

	for (int i = 0; i < 4; i++)
	{
		walls.push_back(Wall());
	}

	walls[0].firstPoint = Vector(50, 50);
	walls[0].secondPoint = Vector(380, 50);

	walls[1].firstPoint = Vector(380, 50);
	walls[1].secondPoint = Vector(380, 330);

	walls[2].firstPoint = Vector(380, 330);
	walls[2].secondPoint = Vector(50, 330);

	walls[3].firstPoint = Vector(50, 330);
	walls[3].secondPoint = Vector(50, 50);

	walls[0].updateNormal();
	walls[1].updateNormal();
	walls[2].updateNormal();
	walls[3].updateNormal();
}

void GameWallAvoidance::exit(SteeringManager* s)
{
	delete sprite1;
	delete sprite;
}

void GameWallAvoidance::execute(SteeringManager* s)
{
	//when the game starts it doesn't call enter for us, so we need to call it ourselves to initialize our sprite
	//sprite and sprite1 will always either be or not be nullptr together
	if (!sprite) enter(s);

	//update sprite
	sprite->draw(s->renderer);
	sprite->update();

	Vector sideWhisker = sprite->getPos() + Vector(SIDE_WHISKER_LENGTH, 0);
	sideWhisker = Vector::rotate_point(sprite->getPos(), sideWhisker, sprite->getAngle());

	SDL_RenderDrawLine(s->renderer, sideWhisker.getX(), sideWhisker.getY(), sprite->getPos().getX(), sprite->getPos().getY());

	sideWhisker = sprite->getPos() + Vector(-SIDE_WHISKER_LENGTH, 0);
	sideWhisker = Vector::rotate_point(sprite->getPos(), sideWhisker, sprite->getAngle());

	SDL_RenderDrawLine(s->renderer, sideWhisker.getX(), sideWhisker.getY(), sprite->getPos().getX(), sprite->getPos().getY());


	sideWhisker = sprite->getPos() + Vector(0, -FRONT_WHISKER_LENGTH);
	sideWhisker = Vector::rotate_point(sprite->getPos(), sideWhisker, sprite->getAngle());

	SDL_RenderDrawLine(s->renderer, sideWhisker.getX(), sideWhisker.getY(), sprite->getPos().getX(), sprite->getPos().getY());

	sprite1->draw(s->renderer);
	sprite1->update();

	for (int i = 0; i < 4; i++)
	{
		walls[i].draw(s->renderer);
	}
}
