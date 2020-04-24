#include "GameWander.h"

GameWander* GameWander::instance = nullptr;

void GameWander::enter(SteeringManager* s)
{
	sprite = new SteeringSprite(200, 200);
	sprite1 = new SteeringSprite(300, 300);
	sprite->wanderOn();
	sprite1->wanderOn();
}

void GameWander::exit(SteeringManager* s)
{
	delete sprite1;
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void GameWander::execute(SteeringManager* s)
{
	//when the game starts it doesn't call enter for us, so we need to call it ourselves to initialize our sprite
	//sprite and sprite1 will always either be or not be nullptr together
	if (!sprite) enter(s);

	//update sprite
	sprite->draw(s->renderer);
	sprite->update();

	sprite1->draw(s->renderer);
	sprite1->update();

	Vector rot = Vector::rotate_point(sprite->getPos(), sprite->getPos() + Vector(0, -100), sprite->angle);

	DrawCircle(s->renderer, rot.getX(), rot.getY(), 25);

	//target rect
	SDL_Rect r;
	r.x = (int)sprite->testVec.getX();
	r.y = (int)sprite->testVec.getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);

	rot = Vector::rotate_point(sprite1->getPos(), sprite1->getPos() + Vector(0, -100), sprite1->angle);

	DrawCircle(s->renderer, rot.getX(), rot.getY(), 25);

	//target rect
	r.x = (int)sprite1->testVec.getX();
	r.y = (int)sprite1->testVec.getY();
	r.h = 5;
	r.w = 5;

	SDL_RenderFillRect(s->renderer, &r);
}
