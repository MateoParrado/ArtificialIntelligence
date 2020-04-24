#include "Fisherman.h"
#include "FishingState.h"
#include "FishermanGlobalState.h"
#include "EntityManager.h"
 
Fisherman::Fisherman(std::string s) : Entity(s)
{
	stateMach = new StateMachine<Fisherman>(this);
	stateMach->setCurrState(Fish);
	stateMach->setGlobState(FishermanGlobal);

	EntityMgr->registerEntity(this);
}