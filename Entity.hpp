#pragma once

#include "Components.hpp"
#include <memory>
#include <string>

class Entity
{
	size_t m_id = 0;
	std::string m_tag = "default";
	bool m_active = true;

	// make constructor private so entity cannot be created directly
	Entity(const std::string& tag, size_t id);
	friend class EntityManager;

public:
	// private member access
	void destroy();
	bool isActive() const;
	const std::string& getTag() const;
	const size_t getId() const;

	// component pointers
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifespan> cLifespan;
	std::shared_ptr<CInput> cInput;
};
