#include "player.h"
#include "maths_funcs.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GL/glut.h> 
#include <assert.h>
#include "tools.h"
#include <iostream>
#define MESHFILE "mesh/tinycity.obj"

player::player(){
	assert(load_mesh(MESHFILE, &vao, &numvertices));
}


int player::getnumVertices(){
	return this->numvertices;
}

GLuint player::getVao(){
	return this->vao;
}