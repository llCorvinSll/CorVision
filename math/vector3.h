#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>


namespace math{

struct Vector2;
struct Vector3;
struct Vector4;
struct quat;
struct Matrix2;
struct Matrix3;
struct Matrix4;

struct Vector3
{
    union
    {
        struct{
            float x;
            float y;
            float z;
        };
        float v[3];
    };

    Vector3() {}

    void set(const float *f){
        x = f[0];
        y = f[1];
        z = f[2];
    }

    void set(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void set(const Vector3 &v){
        x = v.x;
        y = v.y;
        z = v.z;
    }

    void set(const Vector2 &v);
    void set(const Vector4 &v);

    Vector3(const float *f){
        set(f);
    }

    Vector3(float x, float y, float z){
        set(x, y, z);
    }

    Vector3(const Vector3 &v){
        set(v);
    }

    Vector3(const Vector2 &v){
        set(v);
    }

    Vector3(const Vector4 &v){
        set(v);
    }

    Vector3& operator=(const Vector3 &v){
        set(v); return *this;
    }

    Vector3& operator=(const Vector2 &v){
        set(v);
        return *this;
    }

    Vector3& operator=(const Vector4 &v){
        set(v);
        return *this;
    }

    float operator[](int i){
        return v[i];
    }

    float operator[](int i) const {
        return v[i];
    }

    const Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    const Vector3 operator+(const Vector3 &v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    const Vector3 operator-(const Vector3 &v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    const Vector3 operator*(float f) const {
        return Vector3(x * f, y * f, z * f);
    }

    const Vector3 operator/(float f) const {
        return Vector3(x / f, y / f, z / f);
    }

    Vector3& operator+=(const Vector3 &v){
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator-=(const Vector3 &v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3& operator*=(float f){
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector3& operator/=(float f){
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }
};

inline float dot(const Vector3& v1, const Vector3 &v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline const Vector3 cross(const Vector3 &v1, const Vector3 &v2){
    return Vector3(v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

inline float length(const Vector3 &v){
    return sqrtf(dot(v,v));
}

inline float distance(const Vector3 &v1, const Vector3 &v2){
    return length(v1 - v2);
}

inline const Vector3 normalize(const Vector3 &v){
    return v / length(v);
}
}

#endif /* VECTOR3_H */
