#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <string>
#include "player.h"
#include "gl_utils.h"

class gameEngine {
	private:
		float cam_pos[3] = {0.0f, 2.0f, 5.0f}; // don't start at zero, or we will be too close
		float cam_speed = 1.0f; // 1 unit per second
		float cam_yaw_speed = 10.0f; // 10 degrees per second
		float cam_yaw = 0.0f; // y-rotation in degrees
		int view_mat_location=0;
		int proj_mat_location=0;
		player *p;
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
		void initCam();
		void createMenu();
};
#endif