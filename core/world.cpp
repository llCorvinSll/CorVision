#include "world.h"
#include <render/glinclude.h>

namespace core{

World World::Instance;

void World::initWorld(){
    runnig = true;

    Meshes = new render::Mesh*[2];
    Meshes[0] = new render::Mesh();
    Meshes[0]->loadFromOBJ("data/cube.obj");
    Meshes[0]->Create();
    Meshes[1] = new render::Mesh();
    Meshes[1]->loadFromOBJ("data/plane.obj");
    Meshes[1]->Create();
    MeshCount = 2;
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

void World::clearWorld(){
    for(unsigned int i = 0; i < MeshCount ; i++){
        Meshes[i]->Remove();
    }
    delete[] Meshes;

}
}
