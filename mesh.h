#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <cstdio>
#include "obj_loader.h"

class vertex{
    //class defines individual polygon points and their texture coords
	public:
		vertex(const glm::vec3 &pos, const glm::vec2 &texCoord); //constructor
		void setPos(const glm::vec3 &pos); //setting position of vertex
		glm::vec3 *getPos(); //getting position of vertex
		glm::vec2 *getTexCoords(); //getting position of texture coords
	private:
		glm::vec3 pos; //variable for position of vertex point
		glm::vec2 texCoord; //variable for position of texture coord
};

class mesh{
	public:
		void draw(); //drawing mesh
		mesh(vertex* vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndicies); //constructor mesh from array of vertexes
		mesh(const std::string& fileName); //constructor for mesh loaded from file
		~mesh(); //deconstructor
		void updateVertexPoints(vertex* vertices, unsigned int numVertices); //updates position of vertex points
	private:
	    //types of vertex attributes
		enum{
			POSITION_VB,
			TEXCOORD_VB,
			INDEX_VB,
			NUM_BUFFERS
		};
		GLuint mVertexArrayObject; //variable which holds vertexes
		GLuint mVertexArrayBuffers[NUM_BUFFERS]; //variable which holds buffers eg. attributes of vertexes
		unsigned int mDrawCount; //number of vertexes
		void initMesh(const IndexedModel& model); //initialization of mesh
};

#endif //MESH_H
