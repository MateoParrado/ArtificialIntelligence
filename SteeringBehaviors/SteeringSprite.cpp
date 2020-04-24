#include "SteeringSprite.h"
#include "EntityManager.h"

SteeringSprite::SteeringSprite(double x, double y) : SimpleSprite(x, y)
{
	stateMach = new StateMachine<SteeringSprite>(this);
	target = Vector(300, 300);
	EntityMgr->registerEntity(this);
}