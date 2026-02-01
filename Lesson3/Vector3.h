#pragma once
#include <cmath>

// DirectXの種類（XMFLOAT3 など）に関係なく、概念は同じ：
// Vector3 = (x,y,z) の3つのfloatを持つ「位置・方向・速度」などを表す型。
struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

inline Vector3 Add(const Vector3& a, const Vector3& b)
{
    return Vector3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline Vector3 Mul(const Vector3& v, float s)
{
    return Vector3{ v.x * s, v.y * s, v.z * s };
}

inline float Length(const Vector3& v)
{
    return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
