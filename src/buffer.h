#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <string>
#include <iostream>

enum Buffer_Type {
    VAO,
    VBO,
    EBO
};

class Buffer{

private:
    unsigned int VAOs[2];
    unsigned int VBOs[1];
    unsigned int EBOs[1];
public:

    void bindVAO(unsigned int index);
    void bindVBO(unsigned int index);
    void bindEBO(unsigned int index);

    void genVAO(unsigned int index);
    void genVBO(unsigned int index);
    void genEBO(unsigned int index);

    unsigned int getID(Buffer_Type type, unsigned int index);
};




#endif // !BUFFER_H