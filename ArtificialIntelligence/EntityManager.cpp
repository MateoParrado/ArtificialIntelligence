#include "EntityManager.h"

EntityManager* EntityManager::instance = nullptr;

//when an entity is created this is called, used for message handling
void EntityManager::registerEntity(Entity* e)
{
	entityMap.insert(std::pair<int, Entity*>(e->getId(), e));
}

Entity* EntityManager::getEntity(int id)
{
	return entityMap[id];
}

void EntityManager::removeEntity(Entity* e)
{
	entityMap.erase(e->getId());
}

void EntityManager::removeEntity(int id)
{
	entityMap.erase(id);
}