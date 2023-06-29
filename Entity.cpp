#pragma once

#include "Entity.hpp"
#include <string>

Entity::Entity(const std::string& tag, size_t id): m_tag(tag), m_id(id) {};

void Entity::destroy() 
{
	m_active = false;
}

bool Entity::isActive() const
{
	return m_active;
}

const std::string& Entity::getTag() const
{
	return m_tag;
}

const size_t Entity::getId() const
{
	return m_id;
}