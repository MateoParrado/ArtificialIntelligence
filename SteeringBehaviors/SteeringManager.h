#pragma once
#include "StateMachine.h"
#include "SDL.h"

class SteeringManager
{
private:
	StateMachine<SteeringManager>* stateMach;

public:
	SDL_Renderer* renderer;

	SteeringManager(SDL_Renderer* r);

	void update()
	{
		stateMach->update();
	}

	void changeState(State<SteeringManager>* s)
	{
		stateMach->changeState(s);
	}

	void revertState()
	{
		stateMach->revertState();
	}

	~SteeringManager()
	{
		delete stateMach;
	}

};

