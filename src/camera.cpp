#include "camera.h"
#include <math.h>
camera::camera(GLuint *shader_programme,int s_width,int s_height){
	this->target=NULL;
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
}

void camera::setPos(float x,float y,float z){
	cam_pos[0]=x;
	cam_pos[1]=y;
	cam_pos[2]=z;
}

void camera::rotate(float x,float y,float z){
	cam_yaw-=y;
}

void camera::update(){
	mat4 T= identity_mat4();
	if(target!=NULL){
		
		float r=sqrt(get_squared_dist(vec2(target->pos.x(),target->pos.z()),vec2(cam_pos[0],cam_pos[2])));
		r=(float)(((int)(r*100))/100.0f);
		//r=3.0f;

		float new_x=r*cos(target->rotation.v[1]*ONE_DEG_IN_RAD);
		float new_z=r*-sin(target->rotation.v[1]*ONE_DEG_IN_RAD);
		
		cam_pos[0]=new_x;
		cam_pos[2]=new_z;
		vec3 newpos=vec3(new_x,cam_pos[1],new_z);
		//newpos=normalise(newpos);
		//setPos(newpos.x(),cam_pos[1],newpos.z());



		T=look_at(vec3(cam_pos[0],cam_pos[1],cam_pos[2]),target->pos*-1.0f,vec3(0.0f,1.0f,0.0f));
		printf("R:%f\n",r);
		printf("cam_pos (%.3f,%.3f,%.3f) \ntarget_pos (%.3f,%.3f,%.3f) - target_rot(%.3f,%.3f,%.3f)\n",cam_pos[0],cam_pos[1],cam_pos[2],target->pos.v[0],target->pos.v[1],target->pos.v[2],target->rotation.v[0],target->rotation.v[1],target->rotation.v[2]);	
	}else{
		T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
	}
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, T.m);
}