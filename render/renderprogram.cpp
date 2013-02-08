#include "renderprogram.h"
#include "../util/Logger.h"


namespace render{

RenderProgram::RenderProgram(string name){
    ID = glCreateProgram();
    Name = name;
}

bool RenderProgram::createShader(GLenum shaderType, const char *fileName){
    GLuint shader = glCreateShader(shaderType);
    //FILE_READ_SECTION_REMOVE_IT
    FILE *input;
    int fileSize;
    int readed;

    unsigned char * buffer;

    const char mode[] = {'r', 'b' , '\0'};

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
        return false;
    }else{
        glAttachShader(this->ID, shader);
        return true;
    }
}

GLint RenderProgram::_checkShaderStatus(GLuint shader, GLenum param){
    GLint status;
    GLint length;
    GLchar buffer[1024];

    glGetShaderiv(shader, param, &status);
    if (status != GL_TRUE){
        glGetShaderInfoLog(shader, 1024, &length, buffer);
    }
    return status;
}

GLint RenderProgram::getAttribLocation(const GLchar *attrName){
    return glGetAttribLocation(ID,attrName);
}

void RenderProgram::compile(){
    glLinkProgram(this->ID);
}
}
