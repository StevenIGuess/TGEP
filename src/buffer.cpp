#include "buffer.h"


using namespace std;



void Buffer::bindVAO(unsigned int index) {
	glBindVertexArray(VAOs[index]);
}

void Buffer::bindVBO(unsigned int index) {
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[index]);
}

void Buffer::bindEBO(unsigned int index) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[index]);
}

void Buffer::genVAO(unsigned int index){
	glGenVertexArrays(1, &VAOs[index]);
}

void Buffer::genVBO(unsigned int index){
	glGenBuffers(1, &VBOs[index]);
}

void Buffer::genEBO(unsigned int index){
	glGenBuffers(1, &EBOs[index]);
}

unsigned int Buffer::getID(Buffer_Type type, unsigned int index) {

	if(type == VAO) {
		return VAOs[index];
	}
	else if(type == VBO) {
		return VBOs[index];
	}
	else if(type == EBO) {
		return EBOs[index];
	}
	else { 
		throw std::invalid_argument("Invalid type for Buffer_Type");
	}
}

