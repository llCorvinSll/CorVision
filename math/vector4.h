#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>

namespace math{

struct Vector2;
struct Vector3;
struct Vector4;
struct quat;
struct Matrix2;
struct Matrix3;
struct Matrix4;

struct Vector4
{
    union
    {
        struct { float x, y, z, w; };
        float v[4];
    };

    Vector4() {}

    void set(const float *f){
        x = f[0];
        y = f[1];
        z = f[2];
        w = f[3];
    }
    void set(float x, float y, float z, float w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    void set(const Vector4 &v){
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }

    void set(const Vector2 &v);
    void set(const Vector3 &v);

    Vector4(const float *f){
        set(f);
    }
    Vector4(float x, float y, float z, float w){
        set(x, y, z, w);
    }
    Vector4(const Vector4 &v){
        set(v);
    }
    Vector4(const Vector2 &v){
        set(v);
    }
    Vector4(const Vector3 &v){
        set(v);
    }
    Vector4& operator=(const Vector4 &v){
        set(v); return *this;
    }
    Vector4& operator=(const Vector2 &v){
        set(v); return *this;
    }
    Vector4& operator=(const Vector3 &v){
        set(v); return *this;
    }

    float operator[](int i){
        return v[i];
    }
    float operator[](int i) const {
        return v[i];
    }

    const Vector4 operator-() const {
        return Vector4(-x, -y, -z, -w);
    }
    const Vector4 operator+(const Vector4 &v) const {
        return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    const Vector4 operator-(const Vector4 &v) const {
        return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    const Vector4 operator*(float f) const {
        return Vector4(x*f, y*f, z*f, w*f);
    }
    const Vector4 operator/(float f) const {
        return Vector4(x/f, y/f, z/f, w/f);
    }

    Vector4& operator+=(const Vector4 &v){
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }
    Vector4& operator-=(const Vector4 &v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }
    Vector4& operator*=(float f){
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }
    Vector4& operator/=(float f){
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }
};

inline float dot(const Vector4& v1, const Vector4 &v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline float length(const Vector4 &v){
    return sqrtf(dot(v,v));
}

inline float distance(const Vector4 &v1, const Vector4 &v2){
    return length(v1 - v2);
}

inline const Vector4 normalize(const Vector4 &v){
    return v / length(v);
}
}
#endif /* VECTOR4_H */
