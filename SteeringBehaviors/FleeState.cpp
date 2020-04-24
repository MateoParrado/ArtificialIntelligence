#include "FleeState.h"

FleeState* FleeState::instance = nullptr;

void FleeState::enter(SteeringSprite* s)
{
}

void FleeState::exit(SteeringSprite* s)
{
}

void FleeState::execute(SteeringSprite* s)
{
	Vector temp = s->target;
	temp -= s->getPos();
	temp.normalize();
	Vector targetSpeed = temp * SPEED_CAP;
	temp -= s->getVelocity();
	temp.truncate(MAX_FORCE);
	s->setAcceleration(temp / -s->mass);
}
