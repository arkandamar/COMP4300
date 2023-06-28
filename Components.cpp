#include "Components.hpp"

CCollision::CCollision(): radius(0) {};
CCollision::CCollision(float rad) : radius(rad) {};

CScore::CScore(): score(0) {};
CScore::CScore(int s) : score(s) {};

CTransform::CTransform(): pos(Vec2(0,0)), velocity(Vec2(0,0)), angle(0) {};
CTransform::CTransform(const Vec2& p, const Vec2& v) : pos(p), velocity(v) {};