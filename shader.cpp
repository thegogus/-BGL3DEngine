#include "shader.h"

void shader::bind(){
    //binding is telling OpenGL that we use this shader program
	glUseProgram(mGlProgram);
}

GLuint shader::createShader(const std::string &text, GLenum shaderType){
    //defines shader type
	GLuint shader = glCreateShader(shaderType);
	if(shader == 0){
		printf("Error: Shader creation failed!\n");
	}

    //defines variables which will have shader code
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringsLengths[1];

	//getting shader code from text to variables
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringsLengths[0] = text.length();

    //adding shader code to shader program and compiling it
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);
	glCompileShader(shader);

	//checking for errors with shader compilation
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!: ");

	return shader;
}

std::string shader::loadShader(const std::string &fileName){
    //loading text from shader code file
	std::ifstream file(fileName.c_str());
	std::string line;
	std::string output;
	if(file.is_open()){
		while(file.good()){
			getline(file, line);
			output.append(line + "\n");
		}
	}else{
		printf("Unable to load shader: %s\n", fileName.c_str());
	}
	return output;
}

shader::shader(const std::string &fileName){
    //creating shader program and individual shaders from files
	mGlProgram = glCreateProgram();
	mGlShaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	mGlShaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    //attaching shaders to shader program
	for(unsigned int i = 0; i < NUM_SHADERS; i++){
		glAttachShader(mGlProgram, mGlShaders[i]);
	}

	//creating parameters which are going to GPU and we use in shader code
	glBindAttribLocation(mGlProgram, 0, "position");
	glBindAttribLocation(mGlProgram, 1, "texCoord");

	//linking shader
	glLinkProgram(mGlProgram);
	checkShaderError(mGlProgram, GL_LINK_STATUS, true, "Error: Program linking failed!: ");

	//validating shader
	glValidateProgram(mGlProgram);
	checkShaderError(mGlProgram, GL_VALIDATE_STATUS, true, "Error: Program is invalid!: ");

	mGlUniforms[TRANSFORM_U] = glGetUniformLocation(mGlProgram, "transform");

}

void shader::update(const transform &transform, const camera &camera){
    //updating positions of camera and transforming of position of mesh
	glm::mat4 model = camera.getViewProjection() * transform.getModel();
	glUniformMatrix4fv(mGlUniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

void shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage){
    //checking for errors in shaders
	GLint success = 0;
	GLchar error[1024] = {0};
	if(isProgram){
		glGetProgramiv(shader, flag, &success);
	}else{
		glGetShaderiv(shader, flag, &success);
	}
	if(success == GL_FALSE){
		if(isProgram){
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}else{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		printf("%s: '%s'", errorMessage.c_str(), error);
	}

}

shader::~shader(){
    //deleting shaders and cleanup
	for(unsigned int i = 0; i < NUM_SHADERS; i++){
		glDetachShader(mGlProgram, mGlShaders[i]);
		glDeleteShader(mGlShaders[i]);
	}
	glDeleteProgram(mGlProgram);
}
