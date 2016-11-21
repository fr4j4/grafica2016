#include "gameEngine.h"
#include <string>
#include <iostream>
#include "maths_funcs.h"
#include "player.h"

using namespace std;

int g_gl_width = 1280;
int	g_gl_height = 690;
GLFWwindow* g_window = NULL;
gameEngine::gameEngine(){

}

void gameEngine::start(){
	debug("[INFO] Game engine started");
	running=true;
	while(running&& !glfwWindowShouldClose (g_window)){//bucle principal del motor de juegos
		if(!paused){//si no está pausado
			
		}
	}
	debug("[INFO] Game engine stopped");
	glfwTerminate();
}

void gameEngine::pause(bool p){
	if(p){
		debug("[INFO] Game engine paused");
	}else{
		debug("[INFO] Game engine resumed");
	}
		paused=p;
}

void gameEngine::show_main_menu(){
	debug("[INFO] Showing Main Menu");
}

void gameEngine::debug(string msg){
	if(debug_mode==1){
		cout<<msg<<endl;
	}
}
void gameEngine::set_debug_mode(int deb){
	debug_mode=deb;
	cout<<"*** Debug mode set to: "<<deb<<" ***"<<endl;
}

void gameEngine::init(){
	restart_gl_log ();
	start_gl ();
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // set counter-clock-wise vertex order to mean the front
	glClearColor (0.2, 0.2, 0.2, 1.0); // grey background to help spot mistakes
	glViewport (0, 0, g_gl_width, g_gl_height);
}