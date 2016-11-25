#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h> // include GLEW and new version of GL on Windows
//#include <GL/glut.h> 
#include <math.h>
#include "maths_funcs.h"

#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

class camera{
private:
	int screenWidth=0,screenHeight=0;
	float cam_pos[3] = {0.0f, 2.0f, 5.0f}; // don't start at zero, or we will be too close
	vec3 pos;
	float cam_speed = 1.0f; // 1 unit per second
	float cam_yaw_speed = 10.0f; // 10 degrees per second
	float cam_yaw = 0.0f; // y-rotation in degrees
	int view_mat_location=0;
	int proj_mat_location=0;

	// matrix components
	float range;
	float Sx;
	float Sy;
	float Sz;
	float Pz;

public:	

	// input variables
	float near;
	float far;
	float fov;
	float aspect;

	camera(GLuint*,int,int);
	~camera();

	void setPos(float,float,float);
	void move(float,float,float);
	void rotate(float,float,float);
	void update();
};
#endif