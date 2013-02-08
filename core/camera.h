#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include<math/mathgl.h>

namespace core {
using namespace math;
class Camera{
public:
    Camera();
    Camera(float x, float y, float z);
    void setPerspective(float fov, float aspect, float zNear, float zFar);

    //TODO: add normal move and rotation methods
    void moveOnTarget(float speed);
    void strafe(float speed);

    void rotate(float x , float y, float z);

    Matrix4 getViewMatrix();
    Matrix4 getViewProjection();

    void moveEye(float x , float y, float z);
    void moveTarget(float x , float y, float z);
    void moveTop(float x , float y, float z);

    //
    Vector3 Eye;
    Vector3 LookAt;
    Vector3 Top;
    Vector3 Right;
    Matrix4 Projection;


};

}

#endif // CAMERA_H
