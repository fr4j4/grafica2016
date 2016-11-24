#include "player.h"

player::player(const char* file_name){
	assert(load_mesh(file_name, &vao, &numvertices));
}

int player::getnumVertices(){
	return this->numvertices;
}

GLuint player::getVao(){
	return this->vao;
}