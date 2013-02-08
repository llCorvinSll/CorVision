#include "glcontext.h"
#include <stdio.h>
#include <stdlib.h>
#include <util/Logger.h>

namespace render {

//leson2
static const int MESH_VERTEX_COUNT = 3;
static const int VERTEX_SIZE = 6 * sizeof(float);

static const int VERTEX_POSITION_OFFSET = 0;
static const int VERTEX_COLOR_OFFSET    = 3 * sizeof(float);

static const float triangleMesh[MESH_VERTEX_COUNT * 6] = {
    /* 1 вершина, позиция: */ -1.0f, -1.0f, -6.0f, /* цвет: */ 1.0f, 0.0f, 0.0f,
    /* 2 вершина, позиция: */  0.0f,  1.0f, -6.0f, /* цвет: */ 0.0f, 1.0f, 0.0f,
    /* 3 вершина, позиция: */  1.0f, -1.0f, -6.0f, /* цвет: */ 0.0f, 0.0f, 1.0f,
};

static GLuint meshVAO = 0, meshVBO = 0;

void Lesson2(){
    GLint positionLocation, colorLocation;

    // создадим и используем Vertex Array Object (VAO)
    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);
    // создадим и используем Vertex Buffer Object (VBO)
    glGenBuffers(1, &meshVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    // заполним VBO данными треугольника
    glBufferData(GL_ARRAY_BUFFER, MESH_VERTEX_COUNT * VERTEX_SIZE,
                 triangleMesh, GL_STATIC_DRAW);

    // получим позицию атрибута 'position' из шейдера
    positionLocation = GLContext::I().Program.getAttribLocation("position");
    if (positionLocation != -1){
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE,
                              VERTEX_SIZE, (const GLvoid*)VERTEX_POSITION_OFFSET);
        // разрешим использование атрибута
        glEnableVertexAttribArray(positionLocation);
    }

    // получим позицию атрибута 'color' из шейдера
    colorLocation = GLContext::I().Program.getAttribLocation("color");
    if (colorLocation != -1){
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE,
                              VERTEX_SIZE, (const GLvoid*)VERTEX_COLOR_OFFSET);
        // разрешим использование атрибута
        glEnableVertexAttribArray(colorLocation);
    }
}



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
    GLfloat mouseSpeed  = 0.1f;

    float DeltaX =  GLContext::I().SceneParam.midWindowX - (float)mouseX;
    float DeltaY =  GLContext::I().SceneParam.midWindowY - (float)mouseY;

    float camXRot = mouseSpeed * DeltaX;
    float camYRot = mouseSpeed * DeltaY;

    core::World::I().cam.rotate(camYRot, camXRot,0.0f);

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
    Lesson2();
}

void GLContext::renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(Program.getID());
    setupCamera(core::World::I().cam,Program.getID(),math::mat4_identity);

    glBindVertexArray(meshVAO);
    // рендер треугольника из VBO привязанного к VAO
    glDrawArrays(GL_TRIANGLES, 0, MESH_VERTEX_COUNT);


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
