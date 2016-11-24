#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <assert.h>
#include <GL/glew.h>
#include <GL/glut.h> 
#include "tools.h"
#include "maths_funcs.h"
class object{
protected:
	vec3 pos;
	mat4 M;
	GLuint vao, vbo;
	int numvertices;
	int mat_location=0;
public:
	object(const char*,GLuint*);
	~object();
	GLuint getVao();
	int getnumVertices();

	void move(float x,float y,float z);
	void setPos(float x,float y,float z);
	void update();
};
#endif