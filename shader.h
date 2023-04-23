#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <cstdlib>
#include <fstream>
#include "transform.h"
#include "camera.h"

class shader{
	public:
		static GLuint createShader(const std::string &text, GLenum shaderType); //Creates shader from file
		static std::string loadShader(const std::string &fileName); //Loads shader code from file
		static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage); //Check for compilation errors in shader code
		void bind(); //Binds shader
		void update(const transform &transform, const camera &camera); //Updates shader with transform object and camera object
		shader(const std::string& fileName); //constructor for shader with loading from file
		~shader(); //deconstructor
	private:
	    //types of shaders
		enum{
			TRANSFORM_U,
			NUM_UNIFORMS
		};
		static const unsigned int NUM_SHADERS = 2; //number of types of shaders
		GLuint mGlProgram; //shader program
		GLuint mGlShaders[NUM_SHADERS]; //individual shaders
		GLuint mGlUniforms[NUM_UNIFORMS]; //individual uniforms of shaders
};

#endif //SHADER_H
