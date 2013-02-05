#pragma once
#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <core/world.h>
#include "glinclude.h"
#include "../math/mathgl.h"

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

    GLuint createShader(GLenum shaderType, const char *fileName, bool binary);

    GLuint ProgramID = 0;

    math::Matrix4 Projection;


private:

    GLuint _takeProgram();
    GLint _checkShaderStatus(GLuint shader, GLenum param);

    static GLContext Instanse;
    GLContext(){}
    GLContext(const GLContext& root);
    GLContext& operator=(const GLContext&);

    bool _glfwInit();
    bool _glInit();


};
}
#endif // GLCONTEXT_H
