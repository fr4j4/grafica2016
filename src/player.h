#ifndef PLAYER_H
#define PLAYER_H
#include "object3D.h"
#include <string>

using namespace std;
class player{
public:
	//objeto que representa al jugador (por lo general, un auto)
	object3D *object=NULL;
	int infracciones=0;
	string name="Player";

	player(string name);
	~player();
	
};
#endif