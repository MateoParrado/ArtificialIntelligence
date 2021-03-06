#include "SteeringSprite.h"
#include "EntityManager.h"
#include "GameObstacleAvoidance.h"
#include "GameWallAvoidance.h"
#include "GameHide.h"
#include "GamePathFollow.h"

SteeringSprite::SteeringSprite(double x, double y, double minForce, double maxForce, double maxSpeed) : SimpleSprite(x, y, minForce, maxForce, maxSpeed)
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
	if (enabledBehaviors & EVADE)
	{
		force += steer.evade(evadeTarget);
	}
	if (enabledBehaviors & WANDER_OBS_AVOID)
	{
		//if we are in wander obs avoid then get it from that game state
		if(SteeringManager::getInstance()->isInState(GameObstacleAvoidance::getInstance()))
			force += steer.wanderObsAvoid(&wanderTarget, 25, 100, 10, GameObstacleAvoidance::getInstance()->obs);
		else//otherwise we must be in hide so use that
			force += steer.wanderObsAvoid(&wanderTarget, 25, 100, 10, GameHide::getInstance()->obs);
	}
	if (enabledBehaviors & WANDER_WALL_AVOID)
	{
		force += steer.wanderWallAvoid(&wanderTarget, 25, 100, 10, GameWallAvoidance::getInstance()->walls);
	}
	if (enabledBehaviors & INTERPOSE)
	{
		force += steer.interpose(pursuitTarget, evadeTarget);
	}
	if (enabledBehaviors & HIDE)
	{
		force += steer.hide(evadeTarget, GameHide::getInstance()->obs);
	}
	if (enabledBehaviors & PATH_FOLLOW)
	{
		//make sure the path is long enough
		if (!GamePathFollow::getInstance()->path->first || !GamePathFollow::getInstance()->path->first->next) {}
		else
		{
			if (!pathNode)
				pathNode = GamePathFollow::getInstance()->path->first;
			force += steer.pathFollow(&pathNode);
		}
	}
	if (enabledBehaviors & OFFSET_PURSUIT)
	{
		force += steer.offsetPursuit(pursuitTarget, localOffset);
	}

	//make sure we don't get too big forces
	force.truncate(maxForce);

	//or too small forces
	if (force.length() > minForce)
		acceleration = force / mass;
	else
		acceleration = Vector::Zero();

	SimpleSprite::update();

}