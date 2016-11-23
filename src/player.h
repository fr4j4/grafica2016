#ifndef PLAYER_H
#define PLAYER_H
#include "maths_funcs.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GL/glut.h> 
class player{

private:
	vec3 pos;
	GLuint vao, vbo;
	int numvertices;
public:
	player();
	GLuint getVao();
	int getnumVertices();
};

#endif