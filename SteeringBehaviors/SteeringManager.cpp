#include "SteeringManager.h"
#include "GameSeek.h"

SteeringManager* SteeringManager::instance = nullptr;

void SteeringManager::setRenderer(SDL_Renderer* r)
{
	renderer = r;
	stateMach = new StateMachine<SteeringManager>(this);
	stateMach->setCurrState(GameSeek::getInstance()); 
}
