#include "camera.h"

camera::camera(GLuint *shader_programme,int s_width,int s_height){
	screenWidth=s_width;
	screenHeight=s_height;
	// input variables
	near = 0.1f; // clipping plane
	far = 100.0f; // clipping plane
	fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	aspect = (float)screenWidth / (float)screenHeight; // aspect ratio
	// matrix components
	range = tan (fov * 0.5f) * near;
	Sx = (2.0f * near) / (range * aspect + range * aspect);
	Sy = near / range;
	Sz = -(far + near) / (far - near);
	Pz = -(2.0f * far * near) / (far - near);	

	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};

	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
	mat4 view_mat = R * T;
	
	view_mat_location = glGetUniformLocation (*shader_programme, "view");
	glUseProgram (*shader_programme);

	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	proj_mat_location = glGetUniformLocation (*shader_programme, "proj");
	glUseProgram (*shader_programme);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
}

void camera::move(float x,float y,float z){
	cam_pos[0]+=x;
	cam_pos[1]+=y;
	cam_pos[2]+=z;
	update();
}

void camera::setPos(float x,float y,float z){
	cam_pos[0]=x;
	cam_pos[1]=y;
	cam_pos[2]=z;
	update();
}

void camera::rotate(float x,float y,float z){
	cam_yaw-=y;
	update();
}

void camera::update(){
	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
	mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw); // 
	mat4 view_mat = R * T;
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
}