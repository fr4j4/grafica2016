#include "object3D.h"
#include <math.h>

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
	pos.v[0]-=x;
	pos.v[1]-=y;
	pos.v[2]-=z;
}

void object3D::move_forward(float d){
	pos.v[0]+=d*cos(rotation.v[1]*ONE_DEG_IN_RAD);
	pos.v[2]+=d*-sin(rotation.v[1]*ONE_DEG_IN_RAD);
}

void object3D::move_backward(float d){
	pos.v[0]-=d*cos(rotation.v[1]*ONE_DEG_IN_RAD);
	pos.v[2]-=d*-sin(rotation.v[1]*ONE_DEG_IN_RAD);
}

void object3D::setPos(float x,float y,float z){
	pos.v[0]=-1*x;
	pos.v[1]=-1*y;
	pos.v[2]=-1*z;
}

void object3D::rotate(float x,float y,float z){
	//aplico el modulo para que los valores sean entre -360 y 360
	rotation.v[0]-=x;
		rotation.v[0]=fmod(rotation.v[0],360.0f);
	rotation.v[1]-=y;
		rotation.v[1]=fmod(rotation.v[1],360.0f);
	rotation.v[2]-=z;
		rotation.v[2]=fmod(rotation.v[2],360.0f);
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
