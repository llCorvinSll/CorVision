#pragma once
#ifndef RENDERPROGRAM_H
#define RENDERPROGRAM_H
#include "glinclude.h"
#include <string>


namespace render{
using namespace std;

class RenderProgram
{
public:
    RenderProgram(){}
    RenderProgram(string name);

    inline GLuint getID(){
        return ID;
    }

    bool createShader(GLenum shaderType, const char *fileName);
    GLint getAttribLocation(const GLchar * attrName);
    void compile();

    string Name;
protected:
    GLint _checkShaderStatus(GLuint shader, GLenum param);

    GLuint ID;
};
}

#endif // RENDERPROGRAM_H
