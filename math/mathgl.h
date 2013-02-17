#ifndef MATHGL_H
#define MATHGL_H

#include "math3d.h"

namespace math{
// transformation
inline const Matrix4 GLRotationX(float angle){
    const float c = cosf(angle * math_radians), s = sinf(angle * math_radians);
    return Matrix4(1, 0, 0, 0,
                   0, c,-s, 0,
                   0, s, c, 0,
                   0, 0, 0, 1);
}

inline const Matrix4 GLRotationY(float angle){
    const float c = cosf(angle * math_radians), s = sinf(angle * math_radians);
    return Matrix4(c, 0, s, 0,
                   0, 1, 0, 0,
                   -s, 0, c, 0,
                   0, 0, 0, 1);
}

inline const Matrix4 GLRotationZ(float angle){
    const float c = cosf(angle * math_radians), s = sinf(angle * math_radians);
    return Matrix4(c,-s, 0, 0,
                   s, c, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);
}

inline const Matrix4 GLRotation(float x, float y, float z){
    const float cx = cosf(x * math_radians), sx = sinf(x * math_radians),
                cy = cosf(y * math_radians), sy = sinf(y * math_radians),
                cz = cosf(z * math_radians), sz = sinf(z * math_radians);

    // rotationX * rotationY * rotationZ
    return Matrix4(cy * cz, -cy * sz, sy, 0,
                cx * sz + sx * cz * sy, cx * cz - sx * sy * sz, -cy * sx, 0,
                sx * sz - cx * cz * sy, cz * sx + cx * sy * sz, cx * cy, 0,
                0, 0, 0, 1);
}

inline const Matrix4 GLRotation(Vector3 rotation){
    return GLRotation(rotation.x,rotation.y,rotation.z);
}



inline const Matrix4 GLFromEuler(float x, float y, float z){
    const float cx = cosf(x * math_radians), sx = sinf(x * math_radians);
    const float cy = cosf(y * math_radians), sy = sinf(y * math_radians);
    const float cz = cosf(z * math_radians), sz = sinf(z * math_radians);
    // rotationX * rotationY * rotationZ
    return Matrix4(cy * cz, -cy * sz, sy, 0,
                   cx * sz + sx * cz * sy, cx * cz - sx * sy * sz, -cy * sx, 0,
                   sx * sz - cx * cz * sy, cz * sx + cx * sy * sz, cx * cy, 0,
                   0, 0, 0, 1);
}

inline const Matrix4 GLFromEuler(const Vector3 &r){
    return GLFromEuler(r.x, r.y, r.z);
}

inline const Vector3 GLToEuler(const Matrix4 &M){
    Vector3 angle;
    float x, y, C;

    angle.y = asinf(M[2]);
    C       = cosf(angle.y);
    angle.y *= math_degrees;

    if (fabsf(C) > math_epsilon)
    {
        x       =  M[10] / C;
        y       = -M[ 6] / C;
        angle.x = atan2f(y, x) * math_degrees;
        x       =  M[ 0] / C;
        y       = -M[ 1] / C;
        angle.z = atan2f(y, x) * math_degrees;
    } else
    {
        angle.x = 0.0f;
        x       =  M[ 5];
        y       =  M[ 4];
        angle.z = atan2f(y, x) * math_degrees;
    }

    if (angle.x < 0) angle.x += 360;
    if (angle.y < 0) angle.y += 360;
    if (angle.z < 0) angle.z += 360;

    return angle;
}

inline const Matrix4 GLScale(float x, float y, float z){
    return Matrix4(x, 0, 0, 0,
                   0, y, 0, 0,
                   0, 0, z, 0,
                   0, 0, 0, 1);
}

inline const Matrix4 GLScale(const Vector3 &s){
    return GLScale(s.x, s.y, s.z);
}

inline const Matrix4 GLTranslation(float x, float y, float z){
    return Matrix4(1, 0, 0, x,
                   0, 1, 0, y,
                   0, 0, 1, z,
                   0, 0, 0, 1);
}

inline const Matrix4 GLTranslation(const Vector3 &t){
    return GLTranslation(t.x, t.y, t.z);
}

// projection
inline const Matrix4 GLOrthographic(float left, float right,
                                    float bottom, float top,
                                    float zNear, float zFar){
    const float tx = - (right + left) / (right - left);
    const float ty = - (top + bottom) / (top - bottom);
    const float tz = - (zFar + zNear) / (zFar - zNear);
    return Matrix4(2 / (right - left), 0, 0, tx,
                   0, 2 / (top - bottom), 0, ty,
                   0, 0, -2 / (zFar - zNear), tz,
                   0, 0, 0, 1);
}

inline const Matrix4 GLPerspective(float fov, float aspect, float zNear, float zFar){
    const float f = 1 / tanf(fov * math_radians / 2),
            A = (zFar + zNear) / (zNear - zFar),
            B = (2 * zFar * zNear) / (zNear - zFar);

    return Matrix4(f / aspect, 0, 0, 0,
                   0, f, 0, 0,
                   0, 0, A, B,
                   0, 0, -1, 0);
}

inline const Matrix4 GLFrustum(float left, float right,
                               float bottom, float top,
                               float zNear, float zFar){
    return Matrix4((2 * zNear)/(right- left), 0, (right + left) / (right - left), 0,
                   0, (2 * zNear) / (top - bottom), (top + bottom) / (top - bottom), 0,
                   0, 0, -(zFar + zNear) / (zFar - zNear), -(2 * zFar * zNear) / (zFar - zNear),
                   0, 0, -1, 0);
}

// view mtrix
inline const Matrix4 GLLookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up){
    const Vector3 f = normalize(eye - target);
    const Vector3 s = normalize(cross(up, f));
    const Vector3 u = normalize(cross(f, s));

    return Matrix4(s.x, s.y, s.z, -dot(s, eye),
                   u.x, u.y, u.z, -dot(u, eye),
                   f.x, f.y, f.z, -dot(f, eye),
                   0, 0, 0, 1);

    Vector3 zaxis = normalize(target - eye);    // The "look-at" vector.
    Vector3 xaxis = normalize(cross(up, zaxis));// The "right" vector.
    Vector3 yaxis = cross(zaxis, xaxis);     // The "up" vector.

    // Create a 4x4 orientation matrix from the right, up, and at vectors
    Matrix4 orientation = Matrix4(
                xaxis.x, yaxis.x, zaxis.x, 0,
                xaxis.y, yaxis.y, zaxis.y, 0,
                xaxis.z, yaxis.z, zaxis.z, 0,
                0,       0,       0,     1
                );
    // Create a 4x4 translation matrix by negating the eye position.
    Matrix4 translation = Matrix4(
                1,      0,      0,     0,
                0,      1,      0,     0,
                0,      0,      1,     0,
                -eye.x, -eye.y, -eye.z,  1
                );

        // Combine the orientation and translation to compute the view matrix
        return ( translation * orientation );

}

inline const Matrix4 RotateAroundPoint(const Vector3 &p, const Vector3 &angels){
    Matrix4 rm = GLRotation(angels.x,angels.y,angels.z);
    rm.r1[4] = p.x - rm.r1[0]*p.x - rm.r1[1]*p.y - rm.r1[2]*p.z;
    rm.r2[4] = p.y - rm.r2[0]*p.x - rm.r2[1]*p.y - rm.r2[2]*p.z;
    rm.r3[4] = p.z - rm.r3[0]*p.x - rm.r3[1]*p.y - rm.r3[2]*p.z;
    return rm;
}

//TODO: This is poor pice of code need to be rewrited and optimized
inline const Vector3 AxisRotation( Vector3 vec, Vector3 axis, float angle ){
    Vector3 result;
    // The axis is assumed to be normalized:
    //    (just make sure you're not modifying the original)
    axis = normalize(axis);
    // expanded for clarity:
    float u = axis.x;
    float v = axis.y;
    float w = axis.z;
    float x = vec.x;
    float y = vec.y;
    float z = vec.z;
    float c = cosf(angle);
    float s = sinf(angle);
    // Apply the formula verbatim from the linked page:
    result.x = u*(u*x + v*y + w*z)*(1.0f-c) + x*c + (-w*y + v*z)*s;
    result.y = v*(u*x + v*y + w*z)*(1.0f-c) + y*c + ( w*x - u*z)*s;
    result.z = w*(u*x + v*y + w*z)*(1.0f-c) + z*c + (-v*x + u*y)*s;
    return result;
}



}



#endif /* MATHGL_H */
