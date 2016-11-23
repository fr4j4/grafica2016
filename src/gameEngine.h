#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <string>
#include "player.h"
#include "gl_utils.h"

class gameEngine {
	private:
		int debug_mode=0;
		bool 
			running=false,
			paused=false,
			load_lvl=false,
			f1_pressed=false,
			f2_pressed=false,
			f3_pressed=false,
			f4_pressed=false,
			f5_pressed=false
		;

		std::string maps[4]={"map1","map2","map3","map4"};

		void initGL();
		void menu();
	public:
		gameEngine();
		~gameEngine();

		void start();
		void read_input_keys();
		void setScreenSize(int,int);
		void pause(bool p);
		void set_debug_mode(int debug);
		void debug(std::string message,int kind);
		void show_main_menu();
		void load_scenario(std::string scenario_name,player* player);

		void createMenu();
};
#endif