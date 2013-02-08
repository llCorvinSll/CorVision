#include "world.h"
#include <render/glinclude.h>

namespace core{

World World::Instance;

void World::initWorld(){
    runnig = true;
}

void World::pressKeyBoard(int character)
{
    switch(character){
    case 'A':{
        cam.strafe(-1.0f);
        break;
    }
    case 'D':{
        cam.strafe(1.0f);
        break;
    }
    case 'W':{
        cam.moveOnTarget(0.1f);
        break;
    }
    case 'S':{
        cam.moveOnTarget(-0.1f);
        break;
    }
    }

    return;
}

void World::releaseKeyBoard(int character)
{
    switch(character){
    case GLFW_KEY_ESC:{
        runnig = false;
        break;
    }
    default:
        return;
    }
}
}
