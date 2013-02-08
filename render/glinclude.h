#pragma once
#ifndef GLINCLUDE_H
#define GLINCLUDE_H

#include <GL/glew.h>
#include <GL/glfw.h>

//extern GLenum g_OpenGLError = GL_NO_ERROR;

#define OPENGL_CHECK_FOR_ERRORS() \
   { GLenum g_OpenGLError = GL_NO_ERROR; \
    if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) \
        LOG_ERROR("OpenGL error 0x%X\n", (unsigned)g_OpenGLError); }


#endif // GLINCLUDE_H
