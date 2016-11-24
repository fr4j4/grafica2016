#ifndef PLAYER_H
#define PLAYER_H
#include "maths_funcs.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GL/glut.h> 
#include <assert.h>
#include "tools.h"
#include <iostream>
class player{
private:
	vec3 pos;
	GLuint vao, vbo;
	int numvertices;
public:
	player(const char* file_name);
	GLuint getVao();
	int getnumVertices();
};
#endif