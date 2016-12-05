#include "object3D.h"

object3D::object3D(const char* file_name,GLuint* shader_programme){
	this-> shader_programme=shader_programme;
	pos=vec3(0.0f,0.0f,0.0f);
	rotation=vec3(0.0f,0.0f,0.0f);
	assert(load_mesh(file_name, &vao, &numvertices));
	M=identity_mat4 ();
	glUseProgram (*shader_programme);
	mat_location = glGetUniformLocation (*shader_programme, "model");
	update();
	enabled=true;
}

int object3D::getnumVertices(){
	return this->numvertices;
}

GLuint object3D::getVao(){
	return this->vao;
}

void object3D::move(float x,float y,float z){
	pos.v[0]+=x;
	pos.v[1]+=y;
	pos.v[2]+=z;
}

void object3D::setPos(float x,float y,float z){
	pos.v[0]=x;
	pos.v[1]=y;
	pos.v[2]=z;
}

void object3D::rotate(float x,float y,float z){
	rotation.v[0]+=x;
	rotation.v[1]+=y;
	rotation.v[2]+=z;
}

void object3D::update(){
	M =	identity_mat4();//reiniciar la matriz
	M = rotate_y_deg (M, rotation.v[1]);
	M = translate (M, vec3 (-pos.v[0], -pos.v[1], -pos.v[2]));

}
void object3D::render(){
	glUniformMatrix4fv (mat_location, 1, GL_FALSE, M.m);
	glBindVertexArray(getVao());
	glDrawArrays(GL_TRIANGLES,0,getnumVertices());
}
