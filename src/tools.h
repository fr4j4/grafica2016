#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include "gameEngine.h"
// funcion que carga una malla desde filename

bool load_mesh (const char* file_name, GLuint* vao, int* point_count);

void load_player_vehicle();
void load_object(string objectName);

void input_keyb(gameEngine* ge);

#endif 