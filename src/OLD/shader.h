#pragma once 
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
	
public:
	unsigned int ID;

	
	Shader(const char* vertexPath, const char* fragmentPath); //constructor reads & builds shader


	void use(); //glUseProgramm but better
	//nerd shit
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, float value1, float value2, float value3) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
};

#endif // !SHADER_H
