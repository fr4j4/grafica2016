#include "gameEngine.h"
#include <string>
#include <iostream>
#include "maths_funcs.h"
#include "player.h"
#define DBG_INFO 1
#define DBG_WARNING 2
#define DBG_ERROR 3
using namespace std;

int g_gl_width=0;
int	g_gl_height=0;
GLFWwindow* g_window = NULL;

gameEngine::gameEngine(){
	setScreenSize(800,600);
}

void gameEngine::setScreenSize(int width,int height){
	g_gl_height=height;
	g_gl_width=width;
}	

void gameEngine::read_input_keys(){
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose (g_window, 1);
		running=false;
		debug(DBG_INFO,"[INFO] ESC pressed... quitting.");
	}		
}

void gameEngine::start(){
	debug(DBG_INFO,"[INFO] Game engine started");
	initGL();
	running=true;
	while(running&&!glfwWindowShouldClose (g_window)){//bucle principal del motor de juegos
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		// update other events like input handling 
		glfwPollEvents ();
		read_input_keys();
		glfwSwapBuffers (g_window);
	}
	glfwTerminate();
	debug(DBG_INFO,"[INFO] Game engine stopped");
}

void gameEngine::pause(bool p){
	paused=p;
	if(p){
		debug(DBG_INFO,"[INFO] Game engine paused");
	}else{
		debug(DBG_INFO,"[INFO] Game engine resumed");
	}
}

void gameEngine::show_main_menu(){
	debug(DBG_INFO,"[INFO] Showing Main Menu");
}

void gameEngine::debug(int type,string msg){
	string fg_color="",f_color="";
	switch(type){
		case DBG_INFO:
			fg_color="\x1B[40m";
			f_color="\x1B[35m";
		break;
		case DBG_WARNING:
			fg_color="\x1B[40m";
			f_color="\x1B[35m";
		break;
		case DBG_ERROR:
			fg_color="\x1B[40m";
			f_color="\x1B[35m";
		break;

	}
	if(debug_mode==1){
		cout<<fg_color<<f_color<<msg<<"\x1B[0m"<<endl;
	}
}
void gameEngine::set_debug_mode(int deb){
	debug_mode=deb;
	cout<<"*** Debug mode set to: "<<deb<<" ***"<<endl;
}

void gameEngine::initGL(){
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

void gameEngine::load_scenario(std::string scenario_name,player* player){
	debug(DBG_INFO,"Loading scenario "+scenario_name+"...");
}