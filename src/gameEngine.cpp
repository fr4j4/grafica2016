#include "gameEngine.h"
#include <string>
#include <iostream>
#include "maths_funcs.h"
#include "player.h"

using namespace std;

gameEngine::gameEngine(){

}

void gameEngine::start(){
	debug("[INFO] Game engine started");
	running=true;
	while(running){//bucle principal del motor de juegos
		if(!paused){//si no está pausado
			
		}
	}
	debug("[INFO] Game engine stopped");
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