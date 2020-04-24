#include "Chef.h"
#include "CookStewState.h" 
#include "EntityManager.h"

Chef::Chef(std::string s) : Entity(s)
{
	stateMach = new StateMachine<Chef>(this);
	stateMach->setCurrState(CookStew);
	EntityMgr->registerEntity(this);
}