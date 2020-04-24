#include "VehicleSprite.h"

void VehicleSprite::update()
{
	velocity += acceleration;
	localVelocity += localAcceleration;

	Vector temp = velocity;
	temp += Vector::rotate_point(Vector::Zero(), localVelocity, angle - M_PI/2);

	//check if velocity exceeds the cap
	temp.truncate(SPEED_CAP);

	angle = atan2(temp.getY(), temp.getX()) + M_PI/2;

	pos += temp;

	//angularVelocity += angularAcceleration;

	////check if angular velocity exceeds the cap
	//if (angularVelocity < -ANGULAR_SPEED_CAP)
	//{
	//	angularVelocity = -ANGULAR_SPEED_CAP;
	//}
	//else if (angularVelocity > ANGULAR_SPEED_CAP)
	//{
	//	angularVelocity = ANGULAR_SPEED_CAP;
	//}

	//angle += angularVelocity;
}
