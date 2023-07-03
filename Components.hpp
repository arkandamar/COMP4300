#pragma once

#include "Vec2.hpp"
#include "SFML/Graphics.hpp"

class CTransform
{
public:
	Vec2 pos = {0.0, 0.0};
	Vec2 velocity = {0.0, 0.0};
	Vec2 scale = {0.0, 0.0};
	double angle = 0;

	CTransform(const Vec2& p, const Vec2& v, float a);
};

class CShape
{
public:
	sf::CircleShape circle;
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness);
};

class CCollision
{
public:
	float radius = 0;
	CCollision(float rad);
};

class CScore
{

public: 
	int score = 0;
	CScore(int s);
};

class CLifespan
{
public:
	int remaining = 0; // remaining amount of lifespan
	int total = 0; // total inital amount of lifespan
	CLifespan(int total);
};

class CInput
{
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;

	CInput();
};

class CCooldown
{
public:
	int remaining = 0;
	int total = 0;
	CCooldown(int total); // total cooldown (in frame)
};