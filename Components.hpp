#include "Vec2.hpp"

#pragma once
class CCollision
{
	float radius;

public:
	CCollision();
	CCollision(float rad);
};

class CScore
{
	int score;

public: 
	CScore();
	CScore(int s);
};

class CTransform
{
	Vec2 pos;
	Vec2 velocity;
	Vec2 scale;
	double angle;

public:
	CTransform();
	CTransform(const Vec2& p, const Vec2& v);
};