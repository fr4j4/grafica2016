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

void camera::update(float t){
	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
	//mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw); // 
	//mat4 view_mat = R * T;
	mat4 view_mat =T;
	if(target!=NULL){
		//cam_pos[2]=target->pos.v[2];
		//view_mat=translate(view_mat,vec3(0.0f,0.0f,cam_pos[2]+target->pos.v[2]*t));
		//printf("ANTES:cam_pos(%f,%f,%f) - target_pos(%f,%f,%f)\n",cam_pos[0],cam_pos[1],cam_pos[2],target->pos.v[0],target->pos.v[1],target->pos.v[2]);
		float r=sqrt(get_squared_dist(vec3(cam_pos[0],cam_pos[1],cam_pos[2]),target->pos));
		//r=3.0f;
		printf("R:%f\n",r);
		T=identity_mat4();
		float new_x=r*cos((target->rotation.v[1])*ONE_DEG_IN_RAD);
		float new_z=-r*sin((target->rotation.v[1])*ONE_DEG_IN_RAD);
		//setPos(new_x,cam_pos[1],new_z);
		view_mat=look_at(vec3(cam_pos[0],cam_pos[1],cam_pos[2]),target->pos*-1.0f,vec3(0.0f,1.0f,0.0f));
		//printf("DESPUES:cam_pos(%f,%f,%f) - target_pos(%f,%f,%f)\n",cam_pos[0],cam_pos[1],cam_pos[2],target->pos.v[0],target->pos.v[1],target->pos.v[2]);
		printf("cam_pos (%f,%f,%f) - target_rot (%f,%f,%f)\n",cam_pos[0],cam_pos[1],cam_pos[2],target->rotation.v[0],target->rotation.v[1],target->rotation.v[2]);
		//printf("R:%f\n",r );
		//getchar();
	}
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
}