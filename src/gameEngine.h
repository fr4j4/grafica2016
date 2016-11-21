#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>

#include "gl_utils.h"

using namespace std;
class gameEngine {
private:
	int debug_mode=0;
	bool 
		running=false,
		paused=false
	;
public:
	gameEngine();
	~gameEngine();

	void start();
	void pause(bool p);
	void set_debug_mode(int debug);
	void debug(string message);
	void show_main_menu();

};


#endif