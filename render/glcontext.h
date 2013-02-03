#pragma once
#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <main/world.h>
#include "glinclude.h"

namespace render{
class GLContext{
public:    
    static GLContext& I(){
        return Instanse;
    }

    void initContext();
    void renderScene();
    void clearContext();

    void connectToWorld();
private:
    static GLContext Instanse;

    GLContext(){}
    GLContext(const GLContext& root);
    GLContext& operator=(const GLContext&);

    bool _glfwInit();
    bool _glInit();


};
}
#endif // GLCONTEXT_H
