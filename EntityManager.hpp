#pragma once

#include "Entity.hpp"
#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
	EntityVector m_entities;
	EntityMap m_entityMap;
	EntityVector m_toAdd;
	size_t m_total_entities;

public:
	void init();
	void update();
	EntityManager();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	EntityVector& getEntities();
	EntityVector& getEntities(const std::string& tag);
};