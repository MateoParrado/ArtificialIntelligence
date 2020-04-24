#include "VehicleSprite.h"

void VehicleSprite::update()
{
	velocity += acceleration;

	Vector temp = velocity;

	//check if velocity exceeds the cap
	velocity.truncate(SPEED_CAP);

	angle = atan2(velocity.getY(), velocity.getX()) + M_PI/2;

	pos += velocity;
}
