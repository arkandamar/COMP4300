#pragma once
class Vec2
{
	double x;
	double y;

public:
	Vec2();

	Vec2(double xin, double yin);

	bool operator == (const Vec2& v);

	bool operator != (const Vec2& v);

	Vec2 operator + (const Vec2& rhs);

	Vec2 operator - (const Vec2& rhs);

	Vec2 operator * (const Vec2& rhs);

	Vec2 operator / (const Vec2& rhs);

	void normalize();

	double length();
};