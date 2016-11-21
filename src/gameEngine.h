#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <string>
#include "player.h"
#include "gl_utils.h"

class gameEngine {
	private:
		int debug_mode=0
		;
		bool 
			running=false,
			paused=false
		;

		void init();

	public:
		gameEngine();
		~gameEngine();

		void start();
		void pause(bool p);
		void set_debug_mode(int debug);
		void debug(std::string message);
		void show_main_menu();
		void load_scenario(std::string scenario_name,player* player);
};

#endif