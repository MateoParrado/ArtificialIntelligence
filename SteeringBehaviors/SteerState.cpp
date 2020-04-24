#include "SteerState.h"

SteerState* SteerState::instance = nullptr;

void SteerState::enter(SteeringSprite* s)
{
}

void SteerState::exit(SteeringSprite* s)
{
}

void SteerState::execute(SteeringSprite* s)
{	
	Vector temp = s->target;
	temp -= s->getPos();
	temp.normalize();
	Vector targetSpeed = temp * SPEED_CAP;
	temp -= s->getVelocity();
	temp.truncate(MAX_FORCE);
	s->setAcceleration(temp / s->mass);
}
