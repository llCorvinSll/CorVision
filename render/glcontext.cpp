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
    /* 1 вершина, позиция: */ -1.0f, -1.0f, -4.0f, /* цвет: */ 1.0f, 0.0f, 0.0f,
    /* 2 вершина, позиция: */  0.0f,  1.0f, -4.0f, /* цвет: */ 0.0f, 1.0f, 0.0f,
    /* 3 вершина, позиция: */  1.0f, -1.0f, -4.0f, /* цвет: */ 0.0f, 0.0f, 1.0f
};

static GLuint meshVAO = 0, meshVBO = 0;

void Lesson2(){

    //
    glAttachShader(GLContext::I().ProgramID, GLContext::I().createShader(GL_VERTEX_SHADER,"data/lesson.vs",true));
    glAttachShader(GLContext::I().ProgramID, GLContext::I().createShader(GL_FRAGMENT_SHADER,"data/lesson.fs", true));
    // сделаем шейдер активным
    glLinkProgram(GLContext::I().ProgramID);
    glUseProgram(GLContext::I().ProgramID);

    GLContext::I().Projection = math::GLPerspective(45.0f,1024.0/768.0,0.5f,5.0f);
    GLint projMatrixLoc = glGetUniformLocation(GLContext::I().ProgramID, "projectionMatrix");
    if (projMatrixLoc != -1)
        glUniformMatrix4fv(projMatrixLoc, 1, GL_TRUE, GLContext::I().Projection.m);


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
    positionLocation = glGetAttribLocation(GLContext::I().ProgramID, "position");
    if (positionLocation != -1)
    {
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE,
                              VERTEX_SIZE, (const GLvoid*)VERTEX_POSITION_OFFSET);
        // разрешим использование атрибута
        glEnableVertexAttribArray(positionLocation);
    }

    // получим позицию атрибута 'color' из шейдера
    colorLocation = glGetAttribLocation(GLContext::I().ProgramID, "color");
    if (colorLocation != -1){
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE,
                              VERTEX_SIZE, (const GLvoid*)VERTEX_COLOR_OFFSET);
        // разрешим использование атрибута
        glEnableVertexAttribArray(colorLocation);
    }
}



//

void GLFWCALL handleWindowResize(int width, int height){
    const float aspectRatio = (float)width / (float)height;
    GLContext::I().Projection = math::GLPerspective(45.0f,aspectRatio,0.3f,5.0f);
    GLint projMatrixLoc = glGetUniformLocation(GLContext::I().ProgramID, "projectionMatrix");
    if (projMatrixLoc != -1){
        glUniformMatrix4fv(projMatrixLoc, 1, GL_TRUE, GLContext::I().Projection.m);
    }
    LOG_DEBUG( "Windows Resize\n" );
}
void GLFWCALL handleKeyPress( int key, int action ){
    if(action == GLFW_PRESS){
        core::World::I().pressKeyBoard(key);
    }else if(action == GLFW_RELEASE){
        core::World::I().releaseKeyBoard(key);
    }
}

GLContext GLContext::Instanse;

void GLContext::initContext(){
    if(!_glfwInit()){
        LOG_ERROR("Failed to setup GLFW\n" );
    }
    if(!_glInit()){
        LOG_ERROR("Failed to initialize OpenGL\n" );
    }

    ProgramID = _takeProgram();
    Lesson2();
}

void GLContext::renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(ProgramID);

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
}

GLuint GLContext::createShader(GLenum shaderType, const char *fileName, bool binary){
    GLuint shader = glCreateShader(shaderType);
    //FILE_READ_SECTION_REMOVE_IT
    FILE *input;
    int fileSize;
    int readed;

    unsigned char * buffer;

    const char mode[] = {'r', binary ? 'b' : 't', '\0'};

    if ((input = fopen(fileName, mode)) == NULL){
        LOG_ERROR("Opening file '%s'\n", fileName);
        return -1;
    }
    fseek(input,0,SEEK_END);
    fileSize = (int)ftell(input);
    rewind(input);

    if(fileSize == 0){
        LOG_ERROR("Empty file '%s'\n", fileName);
        fclose(input);
        return -1;
    }

    buffer = new unsigned char[fileSize];

    readed = fread(buffer,1,fileSize,input);

    if (readed != fileSize){
        LOG_ERROR("Reading file '%s'\n", fileName);
        delete[] buffer;
        return -1;
    }

    glShaderSource(shader,1,(const GLchar**)&buffer,(const GLint*)&readed);
    glCompileShader(shader);

    delete[] buffer;

    if(_checkShaderStatus(shader,GL_COMPILE_STATUS) != GL_TRUE){
        return -1;
    }else{
        return shader;
    }
}
GLuint GLContext::_takeProgram(){
    return glCreateProgram();
}
GLint GLContext::_checkShaderStatus(GLuint shader, GLenum param){
    GLint status;
    GLint length;
    GLchar buffer[1024];

    glGetShaderiv(shader, param, &status);
    if (status != GL_TRUE){
        glGetShaderInfoLog(shader, 1024, &length, buffer);
    }
    return status;
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
    if( !glfwOpenWindow( 800, 600, 0,0,0,0, 32,0, GLFW_WINDOW ) ){
        LOG_ERROR( "Failed to load Window\n" );
        glfwTerminate();
        return false;
    }
    glfwSetWindowTitle( "CorVision" );
    glfwEnable( GLFW_STICKY_KEYS );
    glfwSwapInterval(1);
    return true;
}
bool GLContext::_glInit(){
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClearDepth(1.0f);

    glewExperimental = true;
    if (glewInit() != GLEW_OK){
        LOG_ERROR( "Failed to initialize GLEW\n");
        return -1;
    }
    return true;
}
}
