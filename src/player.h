#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <assert.h>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GL/glut.h> 
#include "tools.h"
#include "maths_funcs.h"

class player{
private:
	vec3 pos;
	mat4 M;
	GLuint vao, vbo;
	int numvertices;
	int mat_location=0;
public:
	player(const char* file_name,GLuint*);
	GLuint getVao();
	int getnumVertices();

	void move(float x,float y,float z);
	void setPos(float x,float y,float z);
	void update();
};
#endif