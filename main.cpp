#include <render/glcontext.h>
#include <core/world.h>
#include <util/Logger.h>


using namespace core;
using namespace render;

int main(/*int argc, char *argv[]*/){

    LoggerCreate("debug.txt");

    World::I().initWorld();

    GLContext::I().initContext();

    GLContext::I().connectToWorld();

    do{
        GLContext::I().renderScene();
    }while(World::I().runnig && glfwGetWindowParam( GLFW_OPENED ) );

    GLContext::I().clearContext();
    return 0;
}

