#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Entity.hpp"

#pragma once
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
	EntityVector& getEntites();
	EntityVector& getEntites(const std::string& tag);
};