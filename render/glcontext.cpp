#include "glcontext.h"
#include <stdio.h>
#include <stdlib.h>

namespace render {

void GLFWCALL handleKeyPress( int key, int action ){
    if(action == GLFW_PRESS){
        core::World::I().pressKeyBoard(key);
    }else if(action == GLFW_RELEASE){
        core::World::I().releaseKeyBoard(key);
    }
}

GLContext GLContext::Instanse;

void GLContext::initContext(){
    if(_glfwInit()){
        fprintf( stderr, "Failed to initialize GLFW\n" );
    }
    if(_glInit()){
        fprintf( stderr, "Failed to initialize OpenGL\n" );
    }
}

void GLContext::renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers();
}

void GLContext::clearContext(){
    glfwTerminate();
}

void GLContext::connectToWorld(){
    glfwSetKeyCallback(handleKeyPress);
}

bool GLContext::_glfwInit(){
    if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return false;
    }
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) ){
        fprintf( stderr, "Failed to load Window\n" );
        glfwTerminate();
        return false;
    }
    glfwSetWindowTitle( "CorVision" );
    glfwEnable( GLFW_STICKY_KEYS );
    glfwSwapInterval( 1 );
    return true;
}

bool GLContext::_glInit(){
    glShadeModel(GL_SMOOTH);
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClearDepth(0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); //For alpha (now dont need)
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    return true;
}
}
