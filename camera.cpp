#include "camera.h"

camera::camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar){
    //creates perspective from field of view aspect and clipping parameters
    mPerspective = glm::perspective(fov, aspect, zNear, zFar);
    //position of camera
    mPosition = pos;
    //default forward position of camera
    mForward = glm::vec3(0.0f, 0.0f, 1.0f);
    //default up position of camera
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 camera::getViewProjection() const{
    //outputs view projection through perspective
    return mPerspective * glm::lookAt(mPosition, mPosition + mForward, mUp);
}

void camera::setPosition(const glm::vec3 pos){
    //sets position of camera
    mPosition = pos;
}
