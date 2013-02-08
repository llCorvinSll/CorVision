#pragma once
#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "../math/mathgl.h"
#include <core/world.h>
#include <core/camera.h>
#include "renderprogram.h"

namespace render{

struct GLSceneParams{
    int Width/* = 1024*/;
    int Height/* = 768*/;

    float midWindowX/* = 1024/2*/;
    float midWindowY/* = 768/2*/;

    float FOV/* = 45.0f*/;

    float zNear/* = 0.5f*/;
    float zFar/* = 100.0f*/;

    float AspectRatio;

    GLSceneParams(){
        Width = 1024;
        Height = 768;

        midWindowX = 1024.0/2.0;
        midWindowY = 768.0/2.0;

        FOV = 45.0f;

        zNear = 0.5f;
        zFar = 100.0f;
    }
};

class GLContext{
public:    
    static GLContext& I(){
        return Instanse;
    }
    void initContext();
    void renderScene();
    void clearContext();
    void connectToWorld();


    void setupCamera(core::Camera camera, GLuint Program, math::Matrix4 model);

    GLSceneParams SceneParam;

    RenderProgram Program;

 //TRGGERS
    void onWindowResize(int width, int height);
private:
    static GLContext Instanse;
    GLContext() {}
    GLContext(const GLContext& root);
    GLContext& operator=(const GLContext&);

    bool _glfwInit();
    bool _glInit();


};
}
#endif // GLCONTEXT_H
