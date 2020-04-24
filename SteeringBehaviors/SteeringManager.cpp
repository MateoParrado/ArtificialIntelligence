#include "SteeringManager.h"
#include "GameSeek.h"

SteeringManager::SteeringManager(SDL_Renderer* r) : renderer(r)
{
	stateMach = new StateMachine<SteeringManager>(this);
	stateMach->setCurrState(GameSeek::getInstance());
}
