#include "SteeringSprite.h"
#include "EntityManager.h"

//TODO MAKE ARRIVE END ON TIP

SteeringSprite::SteeringSprite(double x, double y) : SimpleSprite(x, y)
{
	//initialize to be doing nothing
	seek = flee = arrive = wander = pursuit = false;

	target = Vector(300, 300);
	EntityMgr->registerEntity(this);
}

void SteeringSprite::update()
{
	Vector force = Vector::Zero();

	//check what behaviors are active and do them if they are
	if (seek)
	{
		force += steer.seek();
	}
	if (flee)
	{
		force += steer.flee();
	}
	if (arrive)
	{
		//force += steer.arrive(target, Vector::rotate_point(pos, Vector(pos.getX(), pos.getY() - 20), angle), this->velocity, 1);
		force += steer.arrive(1);
	}
	if (wander)
	{
		force += steer.wander(25, 100, 10);
	}
	if (pursuit)
	{
		force += steer.pursuit(targetSprite);
	}

	force.truncate(MAX_FORCE);

	acceleration = force / mass;

	SimpleSprite::update();
}