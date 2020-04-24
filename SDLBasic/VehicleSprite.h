#pragma once
#include "Sprite.h"
#include "Definitions.h"

class VehicleSprite :
	public Sprite
{
protected:
	Vector velocity;
	Vector acceleration;

	Vector localVelocity;
	Vector localAcceleration;

	//double angularAcceleration, angularVelocity;
	double angle;


public:
	double mass;

	VehicleSprite(double x, double y, double mass) : Sprite(x, y), velocity(0, 0), acceleration(0, 0), mass(mass),
										localVelocity(0, 0), localAcceleration(0, 0),
										angle(-M_PI/2)//, angularAcceleration(0), angularVelocity(0)
	{

	};

	virtual void update();

	void setVelocity(double xv, double yv)
	{
		velocity = Vector(xv, yv);
	}

	void setVelocity(const Vector& vec)
	{
		velocity = vec;
	}

	void setAcceleration(double xv, double yv)
	{
		acceleration = Vector(xv, yv);
	}

	void setAcceleration(const Vector& vec)
	{
		acceleration = vec;
	}

	void setLocalVelocity(double xv, double yv)
	{
		localVelocity = Vector(xv, yv);
	}

	void setLocalVelocity(const Vector& vec)
	{
		localVelocity = vec;
	}

	void setLocalAcceleration(double xv, double yv)
	{
		localAcceleration = Vector(xv, yv);
	}

	void setLocalAcceleration(const Vector& vec)
	{
		localAcceleration = vec;
	}

	void applyForce(Vector force)
	{
		acceleration += (force /= mass);
	}

	Vector getVelocity() const
	{
		return velocity;
	}

	//void setAngularVelocity(double vel)
	//{
	//	angularVelocity = vel;
	//}

	//void setAngularAcceleration(double vel)
	//{
	//	angularAcceleration = vel;
	//}
};

