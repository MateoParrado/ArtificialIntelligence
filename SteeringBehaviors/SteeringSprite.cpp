#include "SteeringSprite.h"
#include "EntityManager.h"

SteeringSprite::SteeringSprite(double x, double y) : SimpleSprite(x, y)
{
	//initialize to be doing nothing
	enabledBehaviors = 0;
	EntityMgr->registerEntity(this);
}

void SteeringSprite::update()
{
	Vector force = Vector::Zero();

	//check what behaviors are active and do them if they are
	if (enabledBehaviors & SEEK)
	{
		force += steer.seek(seekTarget);
	}
	if (enabledBehaviors & FLEE)
	{
		force += steer.flee(fleeTarget);
	}
	if (enabledBehaviors & ARRIVE)
	{
		//force += steer.arrive(target, Vector::rotate_point(pos, Vector(pos.getX(), pos.getY() - 20), angle), this->velocity, 1);
		force += steer.arrive(arriveTarget, 1);
	}
	if (enabledBehaviors & WANDER)
	{
		force += steer.wander(&wanderTarget, 25, 100, 10);
	}
	if (enabledBehaviors & PURSUE)
	{
		force += steer.pursuit(pursuitTarget);
	}

	force.truncate(MAX_FORCE);

	acceleration = force / mass;

	SimpleSprite::update();
}