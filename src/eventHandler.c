#include "eventHandler.h"

void processKeyboardEvents(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { //close windows when esc is pressed
		glfwSetWindowShouldClose(window, true);
    }

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) { // F1 = Render mode fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		printf("%s", "Render Mode: Fill");
	}

	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) { // F2 == Render mode Line
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		printf("%s", "Render Mode: Line");
	}

    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS) { // F3 == Render mode Point
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		printf("%s", "Render Mode: Point");
	}
}