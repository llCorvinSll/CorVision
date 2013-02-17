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
    Vector3 direction = normalize(LookAt - Eye);
    Eye += direction * speed;
    LookAt += direction * speed;
}

void Camera::strafe(float speed){
    Vector3 direction = normalize(LookAt - Eye);
    direction = normalize(cross(direction,Top));
    Eye += direction * speed;
    LookAt += direction * speed;
}

void Camera::rotate(float x, float y, float z){
    Yaw(x);
//    Pitch(y);

}

void Camera::Yaw(float angelX){
    Vector3 direction = normalize(LookAt - Eye);
    direction = normalize(cross(direction,Top));
//TODO: Remove magic vectors (this is a World Up)
    LookAt = AxisRotation(LookAt,Vector3(0.0f,1.0f,0.0f),angelX);
    Right = normalize(cross(LookAt,Vector3(0.0f,1.0f,0.0f)));
    Top = cross(Right,LookAt);
}

void Camera::Pitch(float angleY){
    LookAt = AxisRotation(LookAt, Right, angleY );
     //RightVector doesn't change!
     Top = cross( Right, LookAt );
}

Matrix4 Camera::getViewMatrix(){
    return GLLookAt(Eye, LookAt,Top);
}
Matrix4 Camera::getViewProjection(){
    return getViewMatrix() * Projection;
}

}
