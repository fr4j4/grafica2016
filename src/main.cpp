#include <iostream>
#include "gameEngine.h"

using namespace std;
int main(int argc, char const *argv[]){
	
	int debug_mode=0;

	if(argv[1]){
		debug_mode=atoi(argv[1]);
	}
	
	gameEngine *ge=new gameEngine();
	ge->set_debug_mode(debug_mode);
	ge->start();
	
	return 0;
}