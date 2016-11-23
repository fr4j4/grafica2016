#include <string>
#include <iostream>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GL/glut.h> 
#include "maths_funcs.h"
#include "gameEngine.h"
#include "player.h"
#include "tools.h"

#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

#define DBG_DBG 0
#define DBG_INFO 1
#define DBG_WARNING 2
#define DBG_ERROR 3
#define DBG_MSG 4
#define DBG_KEY_PRESSED 5
#define DBG_KEY_RELEASED 6

#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"

#include <math.h>

using namespace std;

int g_gl_width=0;
int	g_gl_height=0;
GLFWwindow* g_window = NULL;
GLuint shader_programme;


gameEngine::gameEngine(){
	setScreenSize(800,600);
	debug_mode=1;
}

void gameEngine::setScreenSize(int width,int height){
	g_gl_height=height;
	g_gl_width=width;
	debug("Screen size set at "+to_string(width)+"x"+to_string(height)+".",DBG_INFO);
}	

void gameEngine::read_input_keys(){
	string nombre_mapa="";
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose (g_window, 1);
		running=false;
		debug("ESC",DBG_KEY_PRESSED);
		debug("ESC pressed... quitting.",DBG_INFO);
	}
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_C)) {
		debug("C",DBG_KEY_PRESSED);
		if (system("CLS")) system("clear");
	}
	if(!load_lvl){
		if(!f1_pressed&&GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_F1)){
			load_lvl=true;
			f1_pressed=true;
			nombre_mapa=maps[0];
			debug("F1",DBG_KEY_PRESSED);
		}
		if(f1_pressed&&GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_F1)){
			f1_pressed=false;
			debug("F1",DBG_KEY_RELEASED);
		}
		if(!f2_pressed&&GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_F2)){
			load_lvl=true;
			f2_pressed=true;
			nombre_mapa=maps[1];
			debug("F2",DBG_KEY_PRESSED);
		}
		if(f2_pressed&&GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_F2)){
			f2_pressed=false;
			debug("F2",DBG_KEY_RELEASED);
		}

		if(!f3_pressed&&GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_F3)){
			load_lvl=true;
			f3_pressed=true;
			nombre_mapa=maps[2];
			debug("F3",DBG_KEY_PRESSED);
		}
		if(f3_pressed&&GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_F3)){
			f3_pressed=false;
			debug("F3",DBG_KEY_RELEASED);
		}
		if(!f4_pressed&&GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_F4)){
			load_lvl=true;
			f4_pressed=true;
			nombre_mapa=maps[3];
			debug("F4",DBG_KEY_PRESSED);
		}
		if(f4_pressed&&GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_F4)){
			f4_pressed=false;
			debug("F4",DBG_KEY_RELEASED);
		}

	}if(load_lvl){
		if(nombre_mapa!=""){
			debug("loading level...["+nombre_mapa+"]",DBG_INFO);
			load_scenario(nombre_mapa,NULL);
		}
		load_lvl=false;
	}
}

void gameEngine::start(){
	initGL();
	initCam();
	running=true;
	while(running&&!glfwWindowShouldClose (g_window)){//bucle principal del motor de juegos
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
		_update_fps_counter (g_window);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		glUseProgram (shader_programme);
		glfwPollEvents ();
		

		glBindVertexArray(p->getVao());
		glDrawArrays(GL_TRIANGLES,0,p->getnumVertices());


		cam_pos[2]-=0.25f*elapsed_seconds;
		
		read_input_keys();
	//if (true) {
		mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
		mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw); // 
		mat4 view_mat = R * T;
		glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	//}

	glfwSwapBuffers (g_window);
	}


	glfwTerminate();
	debug("Game engine stopped",DBG_INFO);

}

void gameEngine::initCam(){
	p=new player();
	debug("Player created",DBG_DBG);
	debug("Game engine started",DBG_INFO);

	#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
	// input variables
	float near = 0.1f; // clipping plane
	float far = 100.0f; // clipping plane
	float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	float aspect = (float)g_gl_width / (float)g_gl_height; // aspect ratio
	// matrix components
	float range = tan (fov * 0.5f) * near;
	float Sx = (2.0f * near) / (range * aspect + range * aspect);
	float Sy = near / range;
	float Sz = -(far + near) / (far - near);
	float Pz = -(2.0f * far * near) / (far - near);

	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};

	
	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
	mat4 view_mat = R * T;

	view_mat_location = glGetUniformLocation (shader_programme, "view");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	proj_mat_location = glGetUniformLocation (shader_programme, "proj");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
}

void gameEngine::pause(bool p){
	paused=p;
	if(p){
		debug("Game engine paused",DBG_INFO);
	}else{
		debug("Game engine resumed",DBG_INFO);
	}
}

void gameEngine::show_main_menu(){
	debug("Showing Main Menu",DBG_INFO);
}

void gameEngine::debug(string msg,int kind=0){
	string fg_color="",f_color="\x1B[36m";
	string prefix=" [\x1B[36m--DEBUG\x1B[0m] ";
	switch(kind){
		case DBG_INFO:
			prefix=" \x1B[45m\x1B[37m INF \x1B[0m ";
			fg_color="\x1B[40m";
			f_color="\x1B[35m";
		break;
		case DBG_WARNING:
		 	prefix=" \x1B[43m\x1B[37m WAR \x1B[0m ";
			fg_color="\x1B[40m";
			f_color="\x1B[33m";
		break;
		case DBG_ERROR:
			prefix=" \x1B[41m\x1B[37m ERR \x1B[0m ";
			fg_color="\x1B[40m";
			f_color="\x1B[31m";
			break;
		case DBG_MSG:
			prefix=" \x1B[42m\x1B[30m MSG \x1B[0m ";
			fg_color="\x1B[40m";
			f_color="\x1B[32m";
		break;
		case DBG_KEY_PRESSED:
			prefix=" [KEY_PRESSED] ";
			fg_color="\x1B[40m";
			f_color="\x1B[37m";
		break;
		case DBG_KEY_RELEASED:
			prefix=" [DBG_KEY_RELEASED] ";
			fg_color="\x1B[40m";
			f_color="\x1B[37m";
		break;
		default:
			break;
	}
	if(debug_mode==1){
		cout<<prefix<<fg_color<<f_color<<msg<<"\x1B[0m"<<endl;
	}
}
void gameEngine::set_debug_mode(int deb){
	debug_mode=1;
	if(deb==1){
		debug("Debug mode: ENABLED",DBG_MSG);
	}else{
		debug("Debug mode: DISABLED",DBG_MSG);
	}
	debug_mode=deb;	
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
	shader_programme = create_programme_from_files (VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
}

void gameEngine::load_scenario(std::string scenario_name,player* player){
	debug("Loading scenario..."+scenario_name+"...",DBG_INFO);
	pause(true);

	pause(false);
	debug("Scenario loaded!"+scenario_name+"...",DBG_INFO);
}