#include "EntityManager.hpp"
#include "Entity.hpp"
#include <memory>

EntityManager::EntityManager(): m_total_entities(0) {};

void EntityManager::update()
{
	for (auto e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
	m_toAdd.clear();

	for (auto e : m_entities)
	{

	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) 
{
	std::shared_ptr<Entity> e = std::make_shared<Entity>(tag, m_total_entities++);
	m_toAdd.push_back(e);
	return e;
};

EntityVector& EntityManager::getEntites()
{
	return m_entities;
}

EntityVector& EntityManager::getEntites(const std::string& tag)
{
	return m_entityMap[tag];
}