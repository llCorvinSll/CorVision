#pragma once
#ifndef MATRIX3_H
#define MATRIX3_H

#include <cmath>


namespace math{

struct vec2;
struct Vector3;
struct Vector4;
struct quat;
struct Matrix2;
struct Matrix3;
struct Matrix4;


struct Matrix3
{
    union
    {
        struct {
            float r1[3];
            float r2[3];
            float r3[3];
        };
        float m[9];
    };

    Matrix3() {}

    void set(const float *f){
        m[0] = f[0]; m[1] = f[1]; m[2] = f[2];
        m[3] = f[3]; m[4] = f[4]; m[5] = f[5];
        m[6] = f[6]; m[7] = f[7]; m[8] = f[8];
    }

    void set(float m0, float m1, float m2,
             float m3, float m4, float m5,
             float m6, float m7, float m8){
        m[0] = m0; m[1] = m1; m[2] = m2;
        m[3] = m3; m[4] = m4; m[5] = m5;
        m[6] = m6; m[7] = m7; m[8] = m8;
    }
    void set(const Matrix3 &M){
        m[0] = M[0]; m[1] = M[1]; m[2] = M[2];
        m[3] = M[3]; m[4] = M[4]; m[5] = M[5];
        m[6] = M[6]; m[7] = M[7]; m[8] = M[8];
    }

    void set(const Matrix2 &M);
    void set(const Matrix4 &M);
    void set(const quat &q);

    Matrix3(const float *f){
        set(f);
    }

    Matrix3(const Matrix3 &M){
        set(M);
    }

    Matrix3(const Matrix2 &M){
        set(M);
    }

    Matrix3(const Matrix4 &M){
        set(M);
    }

    Matrix3(const quat &q){
        set(q);
    }

    Matrix3(float m0, float m1, float m2,
            float m3, float m4, float m5,
            float m6, float m7, float m8){
        set(m0, m1, m2,
            m3, m4, m5,
            m6, m7, m8);
    }

    Matrix3& operator=(const Matrix3 &M){
        set(M);
        return *this;
    }

    Matrix3& operator=(const Matrix2 &M){
        set(M);
        return *this;
    }

    Matrix3& operator=(const Matrix4 &M){
        set(M);
        return *this;
    }

    Matrix3& operator=(const quat &q){
        set(q);
        return *this;
    }

    float operator[](int i){
        return m[i];
    }

    float operator[](int i) const {
        return m[i];
    }

    const Matrix3 operator+(const Matrix3 &M) const {
        return Matrix3(m[0] + M[0], m[1] + M[1], m[2] + M[2],
                       m[3] + M[3], m[4] + M[4], m[5] + M[5],
                       m[6] + M[6], m[7] + M[7], m[8] + M[8]);
    }

    const Matrix3 operator-(const Matrix3 &M) const {
        return Matrix3(m[0] - M[0], m[1] - M[1], m[2] - M[2],
                       m[3] - M[3], m[4] - M[4], m[5] - M[5],
                       m[6] - M[6], m[7] - M[7], m[8] - M[8]);
    }

    const Matrix3 operator*(const Matrix3 &M) const {
        return Matrix3(m[0] * M[0] + m[1] * M[3] + m[2] * M[6],
                       m[0] * M[1] + m[1] * M[4] + m[2] * M[7],
                       m[0] * M[2] + m[1] * M[5] + m[2] * M[8],
                       m[3] * M[0] + m[4] * M[3] + m[5] * M[6],
                       m[3] * M[1] + m[4] * M[4] + m[5] * M[7],
                       m[3] * M[2] + m[4] * M[5] + m[5] * M[8],
                       m[6] * M[0] + m[7] * M[3] + m[8] * M[6],
                       m[6] * M[1] + m[7] * M[4] + m[8] * M[7],
                       m[6] * M[2] + m[7] * M[5] + m[8] * M[8]);
    }

    const Matrix3 operator*(float f) const {
        return Matrix3(m[0] * f, m[1] * f, m[2] * f,
                       m[3] * f, m[4] * f, m[5] * f,
                       m[6] * f, m[7] * f, m[8] * f);
    }

    const Matrix3 operator/(float f) const {
        return Matrix3(m[0] / f, m[1] / f, m[2] / f,
                       m[3] / f, m[4] / f, m[5] / f,
                       m[6] / f, m[7] / f, m[8] / f);
    }

    Matrix3& operator+=(const Matrix3 &M){
        m[0] += M[0]; m[1] += M[1]; m[2] += M[2];
        m[3] += M[3]; m[4] += M[4]; m[5] += M[5];
        m[6] += M[6]; m[7] += M[7]; m[8] += M[8];
        return *this;
    }

    Matrix3& operator-=(const Matrix3 &M){
        m[0] -= M[0]; m[1] -= M[1]; m[2] -= M[2];
        m[3] -= M[3]; m[4] -= M[4]; m[5] -= M[5];
        m[6] -= M[6]; m[7] -= M[7]; m[8] -= M[8];
        return *this;
    }

    Matrix3& operator*=(const Matrix3 &M){

        set(m[0] * M[0] + m[1] * M[3] + m[2] * M[6],
            m[0] * M[1] + m[1] * M[4] + m[2] * M[7],
            m[0] * M[2] + m[1] * M[5] + m[2] * M[8],
            m[3] * M[0] + m[4] * M[3] + m[5] * M[6],
            m[3] * M[1] + m[4] * M[4] + m[5] * M[7],
            m[3] * M[2] + m[4] * M[5] + m[5] * M[8],
            m[6] * M[0] + m[7] * M[3] + m[8] * M[6],
            m[6] * M[1] + m[7] * M[4] + m[8] * M[7],
            m[6] * M[2] + m[7] * M[5] + m[8] * M[8]);
        return *this;
    }

    Matrix3& operator*=(float f){
        m[0] *= f; m[1] *= f; m[2] *= f;
        m[3] *= f; m[4] *= f; m[5] *= f;
        m[6] *= f; m[7] *= f; m[8] *= f;
        return *this;
    }

    Matrix3& operator/=(float f){
        m[0] /= f; m[1] /= f; m[2] /= f;
        m[3] /= f; m[4] /= f; m[5] /= f;
        m[6] /= f; m[7] /= f; m[8] /= f;
        return *this;
    }
};

inline float determinant(const Matrix3 &M){
    return M[0] * (M[4] * M[8] - M[5] * M[7])
         - M[1] * (M[3] * M[8] - M[5] * M[6])
         + M[2] * (M[3] * M[7] - M[4] * M[6]);
}

inline const Matrix3 inverse(const Matrix3 &M){
    const float det = 1.0f / determinant(M);

    return Matrix3((M[4] * M[8] - M[5] * M[7]) * det,
                   (M[2] * M[7] - M[1] * M[8]) * det,
                   (M[1] * M[5] - M[2] * M[4]) * det,
                   (M[5] * M[6] - M[3] * M[8]) * det,
                   (M[0] * M[8] - M[2] * M[6]) * det,
                   (M[2] * M[3] - M[0] * M[5]) * det,
                   (M[3] * M[7] - M[4] * M[6]) * det,
                   (M[1] * M[6] - M[0] * M[7]) * det,
                   (M[0] * M[4] - M[1] * M[3]) * det);
}

inline const Matrix3 Transpose(const Matrix3 &M){
    return Matrix3(M[0], M[3], M[6],
                   M[1], M[4], M[7],
                   M[2], M[5], M[8]);
}
}

#endif /* MATRIX3_H */
