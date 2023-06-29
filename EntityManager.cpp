#pragma once

#include "EntityManager.hpp"

EntityManager::EntityManager() {};

void EntityManager::init() {}

void EntityManager::update()
{
	for (auto e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
	m_toAdd.clear();

	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		if (!(*it)->isActive())
		{
			it = m_entities.erase(it);
		}
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) 
{
	// to make entity that has private 
	std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(tag, m_total_entities++));
	m_toAdd.push_back(e);
	return e;
};

EntityVector& EntityManager::getEntities()
{
	return m_entities;
}

EntityVector& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}
