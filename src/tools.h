#ifndef TOOLS_H
#define TOOLS_H
#include "gameEngine.h"
// funcion que carga una malla desde filename

bool load_mesh (const char* file_name, GLuint* vao, int* point_count);

void instantiate_car();
void instantiate_object();

void input_keyb(gameEngine* ge);


#endif 