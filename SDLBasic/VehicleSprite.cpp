#include "VehicleSprite.h"

//handle physics
void VehicleSprite::update()
{
	velocity += acceleration;

	//check if velocity exceeds the cap
	velocity.truncate(maxSpeed);

	//look forwards
	angle = atan2(velocity.getY(), velocity.getX()) + M_PI/2;

	pos += velocity;
}
