#pragma once
#include "Components.hpp"

CTransform::CTransform(const Vec2& p, const Vec2& v, float a) : pos(p), velocity(v), angle(a) {};

CShape::CShape(float radius, int points, const sf::Color& fill
	, const sf::Color& outline, float thickness)
	: circle(radius, points)
{
	circle.setFillColor(fill);
	circle.setOutlineColor(outline);
	circle.setOutlineThickness(thickness);
	circle.setOrigin(radius, radius);
};

CCollision::CCollision(float rad) : radius(rad) {};

CScore::CScore(int s) : score(s) {};

CLifespan::CLifespan(int total) : remaining(total), total(total) {};

CInput::CInput() {};

