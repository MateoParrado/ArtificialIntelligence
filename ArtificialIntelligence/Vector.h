#pragma once
#include <math.h>

struct Vector
{
private:
	double x, y;

public:

	Vector() :x(0), y(0) {}
	Vector(double a, double b) :x(a), y(b) {}

	//get a zero vector
	static Vector Zero()
	{
		return Vector(0, 0);
	}

	//zero this vector
	void zero()
	{
		x = 0;
		y = 0;
	}

	//getters and setters
	double getX() const { return x; }
	double getY() const { return y; }
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	bool isZero() const
	{
		return x || y;
	}

	double length() const
	{
		return sqrt(x*x + y*y);
	}

	double lengthSq() const
	{
		return x * x + y * y;
	}

	//set magnitude to 1
	void normalize() 
	{
		double temp = length();

		x /= temp;
		y /= temp;
	}

	double dot(const Vector& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	//returns 1 if vec is clockwise of this vercotr and -1 if its counterclockwise
	int sign(const Vector& vec) const
	{
		if (y * vec.x > x * vec.y)
		{
			return -1; //counterclockwise
		}
	return 1; //clockwise
	}

	//TODO IMPLEMENT THIS
	//gets the perpendicular vector
	Vector perp() const
	{

	}

	//limit the length to max
	void truncate(double max)
	{
		if (length() < max) return;

		normalize();

		x *= max;
		y *= max;
	}

	double distanceSq(const Vector& vec) const
	{
		return (x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y);
	}

	double distance(const Vector& vec) const
	{
		return sqrt((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y));
	}

	Vector getReverse() const
	{
		return Vector(-x, -y);
	}

	const Vector& operator+=(const Vector& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	const Vector& operator-=(const Vector& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	const Vector& operator*=(const double& val)
	{
		x *= val;
		y *= val;

		return *this;
	}
	const Vector& operator/=(const double& val)
	{
		x /= val;
		y /= val;

		return *this;
	}

	const Vector operator+(const Vector& vec) const
	{
		Vector temp(*this);

		return temp += vec;
	}

	const Vector operator-(const Vector& vec) const
	{
		Vector temp(*this);

		return temp -= vec;
	}

	const Vector operator*(const double& val) const
	{
		Vector v(x, y);

		return v *= val;
	}

	const Vector operator/(const double& val) const
	{
		Vector v(x, y);

		return v /= val;
	}
	
	bool operator==(const Vector& vec)const
	{
		return x == vec.x && y == vec.y;
	}
	bool operator!=(const Vector& vec)const
	{
		return x != vec.x || y != vec.y;
	}

	//this is a method to rotate a point around a point of rotation angle radians
	static Vector& rotate_point(const Vector& center, Vector point, double angle)
	{
		if (!angle) return point;

		double s = sin(angle);
		double c = cos(angle);

		// translate point back to origin:
		point.x -= center.x;
		point.y -= center.y;

		// rotate point
		double xnew = point.x * c - point.y * s;
		double ynew = point.x * s + point.y * c;

		// translate point back:
		point.x = xnew + center.x;
		point.y = ynew + center.y;
		return point;
	}
};