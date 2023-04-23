#include <SDL2/SDL.h>
#include <cstdio>
#include "init.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "texture.h"
#include "camera.h"

int main(int argc, char* argv[]){
    //initialization of SDL2 and OpenGL and creating a window to draw polygons in
    init init(640, 480, "OpenGL TEST");
    //test square from vector points
    vertex vertices[] = {
		vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
		vertex(glm::vec3(-0.10, 0.5, 0), glm::vec2(0.5, 1.0)),
		vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)),
		vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(0, 0))
	};
    //drawing arrangement in test square
	unsigned int indices[] = {
        0, 1, 2
	};
    //loading test square into mesh
    mesh mesh1(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    //loading mesh from file
    mesh home("./homeTest.obj");
    //loading shaders from file
    shader shader("./basicShader");
    //loading texture from file
    texture texture("./gray.png");
    //creating transform object
    transform transform;
    //creating camera
    camera camera(glm::vec3(0.0f, 0.0f, -3.0f), 70.0f, (float)init.getScreenWidth()/(float)init.getScreenHeight(), 0.01f, 1000.0f);

    //creating sdl event for keyboard input
	SDL_Event e;
	bool quit = false;
	//default coords for camera
	float x = 0.0f;
	float y = 0.0f;
	float z = -8.0f;
	//default rotation for mesh
	float r = 0.0f;
	while(!quit){
        //clear screen
	    init.clearScreen(0.1f, 0.0f, 0.0f, 1.0f);
        //binding shader
	    shader.bind();
	    //changing camera position
	    camera.setPosition(glm::vec3(x, y, z));
	    //transforming current mesh eg. changing its position
	    transform.setRot(glm::vec3(0.0f, r, 0.0f));
	    //updating shader
	    shader.update(transform, camera);
	    //binding texture to mesh
	    texture.bindTexture(0);
	    //drawing mesh
	    home.draw();
	    //changing buffers to draw what's in backbuffer eg. drawing mesh on screen
	    init.swapBuffers();
	    //keyboard handling
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                case SDLK_w:
                    z += 0.05f;
                    break;
                case SDLK_s:
                    z -= 0.05f;
                    break;
                case SDLK_a:
                    x += 0.05f;
                    break;
                case SDLK_d:
                    x -= 0.05f;
                    break;
                case SDLK_RIGHT:
                    r += 0.05f;
                    break;
                case SDLK_LEFT:
                    r -= 0.05f;
                    break;
                case SDLK_DOWN:
                    y -= 0.05f;
                    break;
                case SDLK_UP:
                    y += 0.05f;
                    break;
                }
            }
        }
	}
	//safely closing SDL2 and OpenGL
	init.close();
    return 0;
}
