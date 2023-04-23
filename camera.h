#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class camera{
//class creates camera
public:
    camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar); //constructor of camera
    void setPosition(const glm::vec3 pos); //sets position of camera
    glm::mat4 getViewProjection() const; //gets view projection of camera
private:
    glm::mat4 mPerspective; //variable for perspective
    glm::vec3 mPosition; //variable for position
    glm::vec3 mForward; //variable for default forward postion
    glm::vec3 mUp; //variable for default up position
};
#endif // CAMERA_H
