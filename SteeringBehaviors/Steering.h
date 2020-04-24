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
		temp *= SPEED_CAP;
		temp -= vel;

		return temp;
	}

	Vector flee(Vector target, Vector pos, Vector vel)
	{
		Vector temp = pos - target;
		temp.normalize();
		temp *= SPEED_CAP;
		temp -= vel;

		return temp;
	}

	Vector arrive(Vector target, Vector pos, Vector vel, double decelRate)
	{
		Vector temp = target - pos;
		
		double dist = temp.length();

		if (dist > 0)
		{
			double speed = dist / 10;

			speed = (speed < SPEED_CAP) ? speed : SPEED_CAP;

			temp.normalize();
			temp *= speed;
			temp -= vel;

			return temp;
		}

		return Vector::Zero();
	}
};

