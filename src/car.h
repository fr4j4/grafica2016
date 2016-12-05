#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <assert.h>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include "tools.h"
#include "maths_funcs.h"
#include "object3D.h"

class car :public object3D{
public:
	car(const char* file_name,GLuint* shader_programme);
	~car();
};
#endif