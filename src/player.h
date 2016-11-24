#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <assert.h>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GL/glut.h> 
#include "tools.h"
#include "maths_funcs.h"
#include "object.h"
class player :public object{
public:
	player(const char* file_name,GLuint* shader_programme);
	~player();
};
#endif