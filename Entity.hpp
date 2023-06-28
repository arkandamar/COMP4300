#include <string>
#include <memory>
#include "Components.hpp"

#pragma once
class Entity
{
	size_t m_id;
	std::string m_tag;
	bool m_active;

public:
	Entity(const std::string& tag, size_t id);
	void destroy();
	std::string& getTag();
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CCollision> cCollision;
};