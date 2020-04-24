#pragma once
#include "Vector.h"

//TODO, MAKE POS PROTECTED AGAIN

//class to store all steering behaviors
//each steering sprite has an instance
//functions return a force, so they can be added together
class Steering
{
public:
	//to towards a target without slowing (passes through)
	Vector seek(Vector target, Vector pos, Vector vel);

	//run away from a target
	Vector flee(Vector target, Vector pos, Vector vel);

	//go to a target and stop
	Vector arrive(Vector target, Vector pos, Vector vel, double decelRate);

};

