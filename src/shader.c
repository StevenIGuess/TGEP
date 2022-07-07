#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

unsigned int compileShader(const char* vertexPath, const char* fragmentPath) {

    unsigned int vertex, fragment;
    char *buffer = 0;
    long length;
    FILE *f = fopen(vertexPath, "rb");

    //read the vertexshader file
    if(f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if(buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    } else {
        printf("ERR:COULD_NOT_OPEN_FILE::VERTEXSHADER\n");
    }

    //create the vertexshader 
    if(buffer) {
        int success;
        
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, (char const * const *)&buffer, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if(!success) {
            char *infoLog;
            infoLog = malloc(512);
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            printf("%s%s", "ERR::SHADER::FRAGMENT::\n", infoLog);
            free(infoLog);
        }
    }

    f = fopen(fragmentPath, "rb");

    //read the fragmentshader file 
    if(f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if(buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    } else {
        printf("ERR:COULD_NOT_OPEN_FILE::FRAGMENTSHADER\n");
    }
    //create the fragment shader
    if(buffer) {
        int success;

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, (char const * const *)&buffer, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            char *infoLog;
            infoLog = malloc(512);
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            printf("%s%s", "ERR::SHADER::VERTEX::\n", infoLog);
            free(infoLog);
        }
    }
    free(buffer);
    
    //create shader program
    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertex);
    glAttachShader(shader, fragment);
    glLinkProgram(shader);

    //delete unused shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}