#include "SteeringSprite.h"
#include "EntityManager.h"

SteeringSprite::SteeringSprite(double x, double y) : SimpleSprite(x, y)
{
	seek = flee = false;

	target = Vector(300, 300);
	EntityMgr->registerEntity(this);
}

void SteeringSprite::update()
{
	Vector force = Vector::Zero();

	if (seek)
	{
		force += steer.seek(target, this->pos, this->velocity);
	}
	if (flee)
	{
		force += steer.flee(target, this->pos, this->velocity);
	}

	force.truncate(MAX_FORCE);

	acceleration = force / mass;

	SimpleSprite::update();
}