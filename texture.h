#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <GL/glew.h>
#include <cassert>
#include "stb_image.h"

class texture{
public:
    texture(const std::string& fileName); //constructor with loading texture from file
    ~texture(); //deconstructor

    void bindTexture(unsigned int unit); //binding texture to mesh
private:
    GLuint mTexture; //variable which contains texture
};
#endif // TEXTURE_H
