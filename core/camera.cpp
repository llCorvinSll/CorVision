#include "camera.h"

namespace core{
Camera::Camera(){
    this->Projection = mat4_identity;
    this->Eye = vec3_zero;
    this->LookAt = Vector3(0.0f,0.0f,-1.0f);
    this->Top = Vector3(0.0f,1.0f,0.0f);
    this->Right = Vector3(1.0f,0.0f,0.0f);
}

Camera::Camera(float x, float y, float z){
    this->Eye = Vector3(x,y,z);
    this->LookAt = Vector3(Eye.x,Eye.y,Eye.z-1);
    this->Projection = mat4_identity;
}

void Camera::setPerspective(float fov, float aspect, float zNear, float zFar){
    this->Projection = GLPerspective(fov,aspect,zNear,zFar);
}

void Camera::moveOnTarget(float speed){
    Vector3 mv = normalize(LookAt - Eye);
    mv.y = 0.0f;
    Eye += mv * speed;
    LookAt += mv * speed;
}

void Camera::strafe(float speed){
    Right = cross(Top, LookAt);
    Vector3 delta = normalize(Right)*speed;
    Eye += delta;
    LookAt += delta;
}

void Camera::rotate(float x, float y, float z){
    Matrix4 rm = RotateAroundPoint(this->Eye,Vector3(x,y,z));
    this->LookAt = rm * this->LookAt;
}

Matrix4 Camera::getViewMatrix(){
    return GLLookAt(Eye, LookAt,Top);
}
Matrix4 Camera::getViewProjection(){
    return getViewMatrix() * Projection;
}

void Camera::moveEye(float x, float y, float z){
    this->Eye += Vector3(x,y,z);
}
void Camera::moveTarget(float x, float y, float z){
    this->LookAt += Vector3(x,y,z);
}
void Camera::moveTop(float x, float y, float z){
    this->Top += Vector3(x,y,z);
}

}
