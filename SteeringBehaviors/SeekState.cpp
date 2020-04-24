#include "SeekState.h"

SeekState* SeekState::instance = nullptr;

void SeekState::enter(SteeringSprite* s)
{
}

void SeekState::exit(SteeringSprite* s)
{
}

void SeekState::execute(SteeringSprite* s)
{	
	Vector temp = s->target;
	temp -= s->getPos();
	temp.normalize();
	Vector targetSpeed = temp * SPEED_CAP;
	temp -= s->getVelocity();
	temp.truncate(MAX_FORCE);
	s->setAcceleration(temp / s->mass);
}
