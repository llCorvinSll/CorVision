#pragma once
#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

namespace math{

struct Vector2;
struct Vector3;
struct Vector4;
struct quat;
struct Matrix2;
struct Matrix3;
struct Matrix4;

struct Vector2
{
    union{
        struct{
            float x;
            float y;
        };
        float v[2];
    };

    Vector2() {}

    void set(const float *f){
        x = f[0];
        y = f[1];
    }

    void set(float x, float y){
        this->x = x;
        this->y = y;
    }

    void set(const Vector2 &v){
        x = v.x;
        y = v.y;
    }

    void set(const Vector3 &v);
    void set(const Vector4 &v);

    Vector2(const float *f){
        set(f);
    }

    Vector2(float x, float y){
        set(x, y);
    }

    Vector2(const Vector2 &v){
        set(v);
    }

    Vector2(const Vector3 &v){
        set(v);
    }

    Vector2(const Vector4 &v){
        set(v);
    }

    Vector2& operator=(const Vector2 &v){
        set(v);
        return *this;
    }

    Vector2& operator=(const Vector3 &v){
        set(v);
        return *this;
    }

    Vector2& operator=(const Vector4 &v){
        set(v);
        return *this;
    }

    float operator[](int i){
        return v[i];
    }

    float operator[](int i) const {
        return v[i];
    }

    const Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    const Vector2 operator+(const Vector2 &v) const {
        return Vector2(x + v.x, y + v.y);
    }

    const Vector2 operator-(const Vector2 &v) const {
        return Vector2(x - v.x, y - v.y);
    }

    const Vector2 operator*(float f) const {
        return Vector2(x * f, y * f);
    }

    const Vector2 operator/(float f) const {
        return Vector2(x / f, y / f);
    }

    Vector2& operator+=(const Vector2 &v){
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& operator-=(const Vector2 &v){
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2& operator*=(float f){
        x *= f;
        y *= f;
        return *this;
    }

    Vector2& operator/=(float f){
        x /= f;
        y /= f;
        return *this;
    }
};

inline float dot(const Vector2& v1, const Vector2 &v2){
    return v1.x * v2.x + v1.y * v2.y;
}


inline float length(const Vector2 &v){
    return sqrtf(dot(v,v));
}

inline float distance(const Vector2 &v1, const Vector2 &v2){
    return length(v1 - v2);
}

inline const Vector2 normalize(const Vector2 &v){
    return v / length(v);
}

}

#endif /* VECTOR2_H */
