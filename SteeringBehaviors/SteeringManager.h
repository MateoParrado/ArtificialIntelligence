#pragma once
#include "StateMachine.h"
#include "SDL.h"

//game controller class
class SteeringManager
{
private:
	//states are game states
	StateMachine<SteeringManager>* stateMach;
	SteeringManager() {}
	SteeringManager(const SteeringManager&) = delete;
	SteeringManager& operator=(const SteeringManager&) = delete;

	static SteeringManager* instance;

public:
	static SteeringManager* getInstance()
	{
		if (!instance) instance = new SteeringManager();

		return instance;
	}

	//stored to pass to states so that they can display their sprites
	SDL_Renderer* renderer;

	void setRenderer(SDL_Renderer* r);

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

	bool isInState(const State<SteeringManager>* s)
	{
		return stateMach->isInState(s);
	}

	~SteeringManager()
	{
		delete stateMach;
	}

};

