#include "SteeringSprite.h"
#include "EntityManager.h"

//TODO MAKE ARRIVE END ON TIP

SteeringSprite::SteeringSprite(double x, double y) : SimpleSprite(x, y)
{
	//initialize to be doing nothing
	seek = flee = arrive = wander = false;

	target = Vector(300, 300);
	EntityMgr->registerEntity(this);
}

void SteeringSprite::update()
{
	Vector force = Vector::Zero();

	//check what behaviors are active and do them if they are
	if (seek)
	{
		force += steer.seek(target, this->pos, this->velocity);
	}
	if (flee)
	{
		force += steer.flee(target, this->pos, this->velocity);
	}
	if (arrive)
	{
		//force += steer.arrive(target, Vector::rotate_point(pos, Vector(pos.getX(), pos.getY() - 20), angle), this->velocity, 1);
		force += steer.arrive(target, this->pos, this->velocity, 1);
	}
	if (wander)
	{
		force += steer.wander(target, pos, 25, 100, 10, angle, &testVec);
	}

	force.truncate(MAX_FORCE);

	acceleration = force / mass;

	SimpleSprite::update();
}