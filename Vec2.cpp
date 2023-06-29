#pragma once

#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2() {};

Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {};

bool Vec2::operator==(const Vec2& v) const
{
    return (x == v.x && y == v.y);
}

bool Vec2::operator!=(const Vec2& v) const
{
    return !(*this == v);
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y); 
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
    return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator*(const float val) const
{
    return Vec2(x * val, y * val);
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
    return Vec2(x / rhs.x, y / rhs.y);
}

Vec2 Vec2::operator/(const float val) const
{
    return Vec2(x / val, y / val);
}

void Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator*=(const Vec2& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

void Vec2::operator*=(const float val)
{
    x *= val;
    y *= val;
}

void Vec2::operator/=(const Vec2& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
}

void Vec2::operator/=(const float val)
{
    x /= val;
    y /= val;
}

void Vec2::normalize()
{
    double len = dist();
    if (len != 0)
    {
        x /= len;
        y /= len;
    }
}

float Vec2::dist()
{
    return std::sqrt(x * x + y * y);
}