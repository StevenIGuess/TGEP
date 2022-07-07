#ifndef HELPER_H
#define HELPER_H
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


/*
define all the callbacks here
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initWindow(int windowWidth, int windowHeigth, const char* Title) {

	glfwInit(); //init glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //version 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); //version 4.2
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //use only core 

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeigth, Title, NULL, NULL); //this creates the glfw window

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //add the func framebuffer_size_callback to the resize callbacc
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //disable the cursor

	return window;
}

int initGlad(GLFWwindow* window) {

	if (window == NULL) {
		printf("%s","ERR::FAILED_TO_INIT_WINDOW");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //make the window the current context 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("%s","ERR::GLAD_INIT_FAILED");
		return -1;
	}

	return 0;
}

#endif //HELPER_H