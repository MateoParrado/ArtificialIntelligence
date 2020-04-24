#pragma once
#include "Entity.h"

#include <map>

//class used to store the ids of all entities, used for message sending
class EntityManager
{
private:
	//typedef for convenience
	typedef std::map<int, Entity*> EntityMap;

	//map of all entities
	EntityMap entityMap;

	EntityManager() {}
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	static EntityManager* instance;
public:
	static EntityManager* getInstance()
	{
		if (!instance) instance = new EntityManager();

		return instance;
	}

	//add an entity to the map
	void registerEntity(Entity* e);

	//get an entity by id from the map
	Entity* getEntity(int id);
	
	//remove an entity from the map
	void removeEntity(Entity* e);
	void removeEntity(int id);
};

#define EntityMgr EntityManager::getInstance()

