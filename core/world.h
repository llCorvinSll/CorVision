#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "camera.h"
#include "../render/mesh.h"

namespace core{
class World{
public:
    static  World& I(){
        return Instance;
    }
    bool runnig;
    void initWorld();
    //IO
    void pressKeyBoard(int character);
    void releaseKeyBoard(int character);


    Camera cam;

    render::Mesh **Meshes;
    unsigned int MeshCount;

    void clearWorld();

private:
    static World Instance;
    World(){}
    World(const World& root);
    World& operator=(const World&);
};
}
#endif // WORLD_H
