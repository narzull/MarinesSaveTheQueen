#include <iostream>
#include "api/Application.hpp"


int main(int argc, char ** argv) {
    //Creatin the application
    api::Application appli("Template OpenGL 3", argc, argv);
    //Launching the loop
    appli.loop();
    return 0;
}
