#include "texture.h"

texture::texture(const std::string& fileName){
    int width, height, numComponents;

    //loading texture from file using library stb_image to temporary variable
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if(imageData == NULL){
        printf("stb_image failed to load texture, for texture: %s\n", fileName.c_str());
    }

    //creating texture container
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    //setting parameters for texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //loading texture into containter
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    //deleting texture from memory because it's loaded into OpenGL texture
    stbi_image_free(imageData);
}

texture::~texture(){
    //deletes texture from texture variable
    glDeleteTextures(1, &mTexture);
}

void texture::bindTexture(unsigned int unit){
    //binding texture eg. making it current texture
    assert(unit >= 0 && unit <= 31);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}
