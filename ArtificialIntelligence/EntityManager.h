#pragma once
#include "Entity.h"

#include <map>

class EntityManager
{
private:
	typedef std::map<int, Entity*> EntityMap;

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

	void registerEntity(Entity* e);

	Entity* getEntity(int id);

	void removeEntity(Entity* e);
	void removeEntity(int id);
};

#define EntityMgr EntityManager::getInstance()

