#pragma once
#ifndef MATRIX2_H
#define MATRIX2_H

#include <cmath>

namespace math{

struct Vector2;
struct Vector3;
struct Vector4;
struct quat;
struct Matrix2;
struct Matrix3;
struct Matrix4;

struct Matrix2
{
    union
    {
        struct{
            float r1[2];
            float r2[2];
        };
        float m[4];
    };

    Matrix2() {}

    void set(const float *f)
    {
        m[0] = f[0]; m[1] = f[1];
        m[2] = f[2]; m[3] = f[3];
    }
    void set(float m0, float m1,
             float m2, float m3)
    {
        m[0] = m0; m[1] = m1;
        m[2] = m2; m[3] = m3;
    }
    void set(const Matrix2 &M)
    {
        m[0] = M[0]; m[1] = M[1];
        m[2] = M[2]; m[3] = M[3];
    }

    void set(const Matrix3 &M);
    void set(const Matrix4 &M);

    Matrix2(const float *f){
        set(f);
    }
    Matrix2(const Matrix2 &M){
        set(M);
    }
    Matrix2(const Matrix3 &M){
        set(M);
    }
    Matrix2(const Matrix4 &M){
        set(M);
    }
    Matrix2(float m0, float m1,
            float m2, float m3)
    {
        set(m0, m1,
            m2, m3);
    }

    Matrix2& operator=(const Matrix2 &M){
        set(M);
        return *this;
    }
    Matrix2& operator=(const Matrix3 &M){
        set(M);
        return *this;
    }
    Matrix2& operator=(const Matrix4 &M){
        set(M);
        return *this;
    }

    float operator[](int i){
        return m[i];
    }
    float operator[](int i) const {
        return m[i];
    }

    const Matrix2 operator+(const Matrix2 &M) const {
        return Matrix2(m[0] + M[0], m[1] + M[1],
                       m[2] + M[2], m[3] + M[3]);
    }
    const Matrix2 operator-(const Matrix2 &M) const {
        return Matrix2(m[0] - M[0], m[1] - M[1],
                       m[2] - M[2], m[3] - M[3]);
    }
    const Matrix2 operator*(const Matrix2 &M) const {
        return Matrix2(m[0] * M[0] + m[1] * M[2],
                       m[0] * M[1] + m[1] * M[3],
                       m[2] * M[0] + m[3] * M[2],
                       m[2] * M[1] + m[3] * M[3]);
    }
    const Matrix2 operator*(float f) const {
        return Matrix2(m[0] * f, m[1] * f,
                       m[2] * f, m[3] * f);
    }
    const Matrix2 operator/(float f) const {
        return Matrix2(m[0] / f, m[1] / f,
                       m[2] / f, m[3] / f);
    }

    Matrix2& operator+=(const Matrix2 &M) {
        m[0] += M[0]; m[1] += M[1];
        m[2] += M[2]; m[3] += M[3];
        return *this;
    }
    Matrix2& operator-=(const Matrix2 &M){
        m[0] -= M[0]; m[1] -= M[1];
        m[2] -= M[2]; m[3] -= M[3];
        return *this;
    }
    Matrix2& operator*=(const Matrix2 &M){
        set(m[0] * M[0] + m[1] * M[2],
            m[0] * M[1] + m[1] * M[3],
            m[2] * M[0] + m[3] * M[2],
            m[2] * M[1] + m[3] * M[3]);
        return *this;
    }
    Matrix2& operator*=(float f){
        m[0] *= f; m[1] *= f;
        m[2] *= f; m[3] *= f;
        return *this;
    }
    Matrix2& operator/=(float f)
    {
        m[0] /= f; m[1] /= f;
        m[2] /= f; m[3] /= f;
        return *this;
    }
};

inline float determinant(const Matrix2 &M){
    return M[0] * M[3] - M[1] * M[2];
}

inline const Matrix2 inverse(const Matrix2 &M){
    const float det = 1.0f / determinant(M);
    return Matrix2(M[3] * det, -M[2] * det,
                  -M[1] * det,  M[0] * det);
}

inline const Matrix2 Transpose(const Matrix2 &M){
    return Matrix2(M[0], M[2],
                   M[1], M[3]);
}
}

#endif /* MATRIX2_H */
