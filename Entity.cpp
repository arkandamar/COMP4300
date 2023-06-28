#include "Entity.hpp"

Entity::Entity(const std::string& tag, size_t id): m_tag(tag), m_id(id), m_active(true) {};

void Entity::destroy() 
{
	m_active = false;
}

std::string& Entity::getTag()
{
	return m_tag;
}