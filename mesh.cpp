#include "mesh.h"
#include "obj_loader.h"

vertex::vertex(const glm::vec3 &pos, const glm::vec2 &texCoord){
    //defines default position and default texture coords for vertex
	this->pos = pos;
	this->texCoord = texCoord;
}

void vertex::setPos(const glm::vec3 &pos){
    //sets position for vertex
	this->pos = pos;
}

glm::vec3 *vertex::getPos(){
    //gets position of vertex
    return &pos;
}

glm::vec2 *vertex::getTexCoords(){
    //gets vertex texture coords
    return &texCoord;
}

mesh::mesh(const std::string& fileName){
    //loads mesh model from file using objloader
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    initMesh(model);
}

mesh::mesh(vertex* vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices){
    //creates mesh from array of vertices
    IndexedModel model;

    for(unsigned int i = 0; i < numVertices; i++){
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTexCoords());
    }

    for(unsigned int i = 0; i < numIndices; i++){
        model.indices.push_back(indices[i]);
    }

    initMesh(model);
}

mesh::~mesh(){
    //deletes mesh
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void mesh::initMesh(const IndexedModel& model){
    //initializes mesh

    //gets number of vertices
    mDrawCount = model.indices.size();

    //generates object of vertex array
    glGenVertexArrays(1, &mVertexArrayObject);
	glBindVertexArray(mVertexArrayObject);

	//generates buffers for vertex array buffers
	glGenBuffers(NUM_BUFFERS, mVertexArrayBuffers);

    //adds attributes to GPU from vertices
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void mesh::updateVertexPoints(vertex* vertices, unsigned int numVertices){
    //updates position of vertex points
    std::vector<glm::vec3> positions;
    positions.reserve(numVertices);
    for(unsigned int i = 0; i < numVertices; i++){
        positions.push_back(*vertices[i].getPos());
    }

    //adds attribute of position of vertcies
    glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * sizeof(positions[0]), &positions[0]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}


void mesh::draw(){
    //draws mesh
	glBindVertexArray(mVertexArrayObject);
	glDrawElements(GL_TRIANGLES, mDrawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
