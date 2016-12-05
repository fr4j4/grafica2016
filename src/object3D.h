#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <assert.h>
#include <GL/glew.h>
#include "tools.h"
#include "maths_funcs.h"
class object3D{
protected:
	vec3 rotation;
	mat4 M;
	GLuint vao, vbo;
	GLuint* shader_programme;
	int numvertices;
	int mat_location=0;
public:
	vec3 pos;
	bool enabled;
	object3D(const char*,GLuint*);
	~object3D();
	GLuint getVao();
	int getnumVertices();
	void move  (float x,float y,float z);
	void setPos(float x,float y,float z);
	void rotate(float x,float y,float z);
	void update();
	void render();
};
#endif