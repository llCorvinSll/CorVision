#include "glcontext.h"
#include <stdio.h>
#include <stdlib.h>
#include <util/Logger.h>

namespace render {
/**********************
 * WINDOW EVENT HANDLERS
 **********************/
void GLFWCALL handleWindowResize(int width, int height){
    GLContext::I().onWindowResize(width,height);
}

void GLFWCALL handleKeyPress( int key, int action ){
    if(action == GLFW_PRESS){
        core::World::I().pressKeyBoard(key);
    }else if(action == GLFW_RELEASE){
        core::World::I().releaseKeyBoard(key);
    }
}

void GLFWCALL handleMouseMove(int mouseX, int mouseY)
{

    //TODO: move logic to World class
    GLfloat mouseSpeed  = 0.0001f;

    float DeltaX = 0;
    float DeltaY = 0;
    DeltaX = (float)mouseX - GLContext::I().SceneParam.midWindowX ;
    DeltaY = (float)mouseY - GLContext::I().SceneParam.midWindowY ;

    float camXRot = DeltaX * mouseSpeed;
    float camYRot = DeltaY * mouseSpeed;


//    if (camXRot < -90.0f){
//        camXRot = -90.0f;
//    }
//    // Limit looking down to vertically down
//    if (camXRot > 90.0f){
//        camXRot = 90.0f;
//    }
//    // Looking left and right. Keep the angles in the range -180.0f (anticlockwise turn looking behind) to 180.0f (clockwise turn looking behind)
//    if (camYRot < -180.0f){
//        camYRot += 360.0f;
//    }
//    if (camYRot > 180.0f){
//        camYRot -= 360.0f;
//    }

    core::World::I().cam.rotate(camXRot , camYRot ,0.0f);

    glfwSetMousePos(GLContext::I().SceneParam.midWindowX,
                    GLContext::I().SceneParam.midWindowY);
}
/**********************
 * END SECTION
 **********************/

GLContext GLContext::Instanse;

void GLContext::initContext(){
    if(!_glfwInit()){
        LOG_ERROR("Failed to setup GLFW\n" );
    }
    if(!_glInit()){
        LOG_ERROR("Failed to initialize OpenGL\n" );
    }

    core::World::I().cam.setPerspective(
                GLContext::I().SceneParam.FOV,
                GLContext::I().SceneParam.AspectRatio,
                GLContext::I().SceneParam.zNear,
                GLContext::I().SceneParam.zFar);

    //TODO: Remove it to coll source load procedure
    Program = RenderProgram("Lesson");
    Program.createShader(GL_VERTEX_SHADER ,"data/lesson.vs");
    Program.createShader(GL_FRAGMENT_SHADER ,"data/lesson.fs");
    Program.compile();
    OPENGL_CHECK_FOR_ERRORS();
}

void GLContext::renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(Program.getID());
    for (uint32_t i = 0; i < core::World::I().MeshCount; ++i){
        setupCamera(core::World::I().cam,Program.getID(),math::mat4_identity);
        core::World::I().Meshes[i]->Render();
    }



    glfwSwapBuffers();
}

void GLContext::clearContext(){
    glfwTerminate();
}

void GLContext::connectToWorld(){
    glfwSetWindowSizeCallback(handleWindowResize);
    glfwSetKeyCallback(handleKeyPress);
    glfwSetMousePosCallback(handleMouseMove);
}

void GLContext::setupCamera(core::Camera camera, GLuint Program, math::Matrix4 model){

    math::Matrix4 result =   camera.Projection * camera.getViewMatrix() * model;

    glUniformMatrix4fv(
                glGetUniformLocation(Program, "projectionMatrix"),
                1,
                GL_TRUE, result.m);
}

void GLContext::onWindowResize(int width, int height){
    GLContext::I().SceneParam.AspectRatio = (float)width / (float)height;
}

bool GLContext::_glfwInit(){
    if( !glfwInit() ){
        LOG_ERROR( "Failed to initialize GLFW\n" );
        return false;
    }
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if( !glfwOpenWindow(
                GLContext::I().SceneParam.Width,
                GLContext::I().SceneParam.Height,
                0,
                0,
                0,
                0,
                32,
                0,
                GLFW_WINDOW) ){
        LOG_ERROR( "Failed to load Window\n" );
        glfwTerminate();
        return false;
    }
    glfwSetWindowTitle( "CorVision" );

    GLContext::I().SceneParam.AspectRatio =
            (float)GLContext::I().SceneParam.Width /
            (float)GLContext::I().SceneParam.Height;


    glfwEnable( GLFW_STICKY_KEYS );
    glfwEnable( GLFW_KEY_REPEAT );

    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(GLContext::I().SceneParam.midWindowX,
                    GLContext::I().SceneParam.midWindowY);


    glfwSwapInterval(1);
    return true;
}

bool GLContext::_glInit(){
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClearDepth(1.0f);
    //    glEnable(GL_CULL_FACE);

    glewExperimental = true;
    if (glewInit() != GLEW_OK){
        LOG_ERROR( "Failed to initialize GLEW\n");
        return -1;
    }
    return true;
}
}
