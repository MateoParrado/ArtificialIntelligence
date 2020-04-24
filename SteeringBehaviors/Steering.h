#pragma once
#include "Vector.h"
#include "Definitions.h"

//TODO, MAKE POS PROTECTED AGAIN

class Steering
{
public:
	Vector seek(Vector target, Vector pos, Vector vel)
	{
		Vector temp = target - pos;
		temp.normalize();
		Vector targetSpeed = temp * SPEED_CAP;
		temp -= vel;

		return temp;
	}

	Vector flee(Vector target, Vector pos, Vector vel)
	{
		Vector temp = pos - target;
		temp.normalize();
		Vector targetSpeed = temp * SPEED_CAP;
		temp -= vel;

		return temp;
	}
};

