#pragma once
#include "Sprite.h"
#include "Definitions.h"

//TODO implement set local acceleration

//a sprite that includes physics capabilities
class VehicleSprite :
	public Sprite
{
protected:
	Vector velocity;
	Vector acceleration;

	double angle;
	double mass;

public:
	const double maxForce, minForce, maxSpeed;


	VehicleSprite(double x, double y, double mass, double minForce, double maxForce, double maxSpeed) : 
		Sprite(x, y), velocity(0, 0), acceleration(0, 0), mass(mass), maxForce(maxForce), minForce(minForce), maxSpeed(maxSpeed),
													 angle(-M_PI/2)
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
		velocity = Vector::rotate_point(Vector::Zero(), Vector(xv, yv), angle - M_PI / 2);
	}

	void setLocalVelocity(const Vector& vec)
	{
		velocity = Vector::rotate_point(Vector::Zero(), vec, angle - M_PI / 2);
	}

	void setLocalAcceleration(double xv, double yv)
	{
		acceleration = Vector::rotate_point(Vector::Zero(), Vector(xv, yv), angle - M_PI / 2);
	}

	void setLocalAcceleration(const Vector& vec)
	{
		acceleration = Vector::rotate_point(Vector::Zero(), vec, angle - M_PI / 2);
	}
	
	void applyForce(Vector force)
	{
		acceleration += (force /= mass);
	}

	Vector getVelocity() const
	{
		return velocity;
	}
};

