#include "world.h"
#include <render/glinclude.h>

namespace core{

World World::Instance;

void World::initWorld(){
    runnig = true;
}

void World::pressKeyBoard(int character)
{
    return;
}

void World::releaseKeyBoard(int character)
{
    switch(character){
    case GLFW_KEY_ESC:
        runnig = false;
    default:
        return;
    }
}
}
