#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class transform{
    //class for transforming mesh
	public:
	    //constructor
		transform(const glm::vec3 &pos = glm::vec3(0, 0, 0), const glm::vec3 &rot = glm::vec3(0, 0, 0), const glm::vec3 &scale = glm::vec3(1.0, 1.0, 1.0));
		glm::mat4 getModel() const; //gets model of transformation eg. it's transformation matrix
		glm::vec3 *getPos(); //gets posistion of transformation
		glm::vec3 *getRot(); //gets rotation of transformation
		glm::vec3 *getScale(); //gets scale of transformation
		void setPos(const glm::vec3& pos); //sets position of transformation
		void setRot(const glm::vec3& rot); //sets rotation of transformation
		void setScale(const glm::vec3& scale); //sets scale of transformation
	private:
		glm::vec3 pos; //variable that stores position
		glm::vec3 rot; //variable that stores rotation
		glm::vec3 scale; //variable that stores scale
};

#endif //TRANSFORM_H
