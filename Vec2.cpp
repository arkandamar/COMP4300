#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {};

Vec2::Vec2(double xin, double yin) : x(xin), y(yin) {};

bool Vec2::operator==(const Vec2& v)
{
    return (x == v.x && y == v.y);
}

bool Vec2::operator!=(const Vec2& v)
{
    return !(*this == v);
}

Vec2 Vec2::operator+(const Vec2& rhs)
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs)
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs)
{
    return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator/(const Vec2& rhs)
{
    return Vec2(x / rhs.x, y / rhs.y);
}

void Vec2::normalize()
{
    double len = length();
    if (len != 0)
    {
        x /= len;
        y /= len;
    }
}

double Vec2::length()
{
    return std::sqrt(x * x + y * y);
}