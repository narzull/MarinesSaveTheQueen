#include <iostream>
#include "api/Application.hpp"


int main(int argc, const char *argv[]) {
	
	// AH LOLZ
	if(argc < 2){
		std::string param = argv[0];
		//Creatin the application
		api::Application appli("Template OpenGL 3", param);
		//Launching the loop
		appli.loop();
	}
	else{
		std::cout << "Not enough argument to launch the application" << std::endl;
	}

    return 0;
}
