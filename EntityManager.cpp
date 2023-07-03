#pragma once

#include <iostream>
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

	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](std::shared_ptr<Entity> e) 
		{ return e->isActive() == false; }
	), m_entities.end());

	// Iterate through the map and erase elements from the vector when a specific condition is fulfilled
	for (auto& pair : m_entityMap) {
		EntityVector& entityVector = pair.second;

		entityVector.erase
		(
			std::remove_if(entityVector.begin(), entityVector.end(), 
			[](std::shared_ptr<Entity> e) { return e->isActive() == false; }), 
			entityVector.end()
		);
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
