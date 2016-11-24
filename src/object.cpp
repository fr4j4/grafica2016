#include "object.h"

object::object(const char* file_name,GLuint* shader_programme){
	pos=vec3(0.0f,0.0f,0.0f);
	assert(load_mesh(file_name, &vao, &numvertices));
	M=identity_mat4 ();
	mat_location = glGetUniformLocation (*shader_programme, "obj");
	glUseProgram (*shader_programme);
	update();
}

int object::getnumVertices(){
	return this->numvertices;
}

GLuint object::getVao(){
	return this->vao;
}

void object::move(float x,float y,float z){
	pos.v[0]+=x;
	pos.v[1]+=y;
	pos.v[2]+=z;
	update();
}

void object::setPos(float x,float y,float z){
	pos.v[0]=x;
	pos.v[1]=y;
	pos.v[2]=z;
	update();
}

void object::update(){
	mat4 T = translate (identity_mat4 (), vec3 (-pos.v[0], -pos.v[1], -pos.v[2])); // cam translation
	//mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw); // 
	//mat4 view_mat = R * T;
	M=T;
	glUniformMatrix4fv (mat_location, 1, GL_FALSE, M.m);
}