#pragma once
#include "StateMachine.h"
#include "SDL.h"

//game controller class
class SteeringManager
{
private:
	//states are game states
	StateMachine<SteeringManager>* stateMach;

public:
	//stored to pass to states so that they can display their sprites
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

