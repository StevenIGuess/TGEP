#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/mesh.h>


#include "buffer.h"
#include "textureLoader.h"
#include "shader.h"
#include "camera.h"
#include "model.h"


//settings
static int SCR_WIDTH = 2048;
static int SCR_HEIGHT = 1080;

//camera 
Camera camera(glm::vec3(0.0f,0.0f,3.0f));
float lastX = SCR_WIDTH/2, lastY = SCR_HEIGHT/2;
bool firstMouse = true;

//timeing
float lastFrame = 0.0f;
float deltaTime = 0.0f;
float currentFrame;
float pos1 = 0.0f;
float pos2 = 0.0f;
float speedOfLightLol = 0.01f;


//model = glm::mat4(1.0f);
//model = glm::translate(model, lightPos);
//model = glm::scale(model, glm::vec3(0.2f)); 

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -7.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, 2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-7.7f,  5.0f, 7.5f),  
    glm::vec3( 5.3f, -2.0f, -2.5f),  
    glm::vec3( 2.5f,  2.0f, -2.5f), 
    glm::vec3( 6.5f,  5.2f, 1.5f), 
    glm::vec3(-10.3f, 1.0f, -13.5f),
	glm::vec3(16.5f,  15.2f, -1.5f), 
    glm::vec3(-8.3f,  7.0f,  3.5f),
	glm::vec3( 1.5f,  -8.2f, 4.5f), 
    glm::vec3(19.3f, 20.0f, -15.5f),
	glm::vec3( 10.5f,  -20.2f, 1.5f), 
    glm::vec3( -19.3f, -20.4f, -2.5f)   
};

glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.7f,  0.2f,  2.0f),
	glm::vec3( 2.3f, -2.3f, -3.0f),
	glm::vec3(-4.0f,  2.0f, -6.0f),
	glm::vec3( 0.0f,  0.0f, -3.0f)
};  


//callbaccs
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

//process input
void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		std::cout << "Render Mode: Fill" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		std::cout << "Render Mode: Wireframe" << std::endl;
	}
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		speedOfLightLol += 0.01f;
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		speedOfLightLol -= 0.01f;
}

//main render loop
void renderLoop(GLFWwindow* window, Shader SPO, Shader LSPO, Buffer B, unsigned int diffuseMap, unsigned int fancyTextureL, unsigned int specularMap, Model testModel) {

	while (!glfwWindowShouldClose(window)) {

		//time and stuff
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//input
		processInput(window, deltaTime);

		//render
        glClearColor(0.03f, 0.03f, 0.03f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if(glfwGetKey(window, GLFW_KEY_ENTER) != GLFW_PRESS)
		{
			pos1 += speedOfLightLol * deltaTime;
			pos2 += speedOfLightLol * deltaTime;
		}
		pointLightPositions[0].x = sin(pos1*3.0f) * 7.5f;
		pointLightPositions[0].z = cos(pos2*3.0f) * 7.5f;

		pointLightPositions[1].x = sin(pos1*3.0f) * 7.5f;
		pointLightPositions[1].y = cos(pos2*3.0f) * 7.5f;

		pointLightPositions[2].y = sin(pos1*3.0f) * 7.5f;
		pointLightPositions[2].z = cos(pos2*3.0f) * 7.5f;

		pointLightPositions[3].z = sin(pos1*3.0f) * 7.5f;
		pointLightPositions[3].y = cos(pos2*3.0f) * 7.5f;

			
		//set variables for normal shader
		SPO.use();	
        SPO.setVec3("viewPos", camera.Position);
        SPO.setFloat("material.shininess", 32.0f);

		glm::vec3 pntLightAmbient = glm::vec3(0.01f, 0.01f, 0.01f);
		glm::vec3 pntLightDiffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		glm::vec3 pntLightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
		float pntLightLinear = 0.062f;
		float pntLightQuadratic = 0.009f;

        // directional light
        SPO.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        SPO.setVec3("dirLight.ambient", 0.01f, 0.01f, 0.01f);
        SPO.setVec3("dirLight.diffuse", 0.2f, 0.2f, 0.2f);
        SPO.setVec3("dirLight.specular", 0.3f, 0.3f, 0.3f);
        // point light 1
        SPO.setVec3("pointLights[0].position", pointLightPositions[0]);
        SPO.setVec3("pointLights[0].ambient", pntLightAmbient);
        SPO.setVec3("pointLights[0].diffuse", pntLightDiffuse);
        SPO.setVec3("pointLights[0].specular", pntLightSpecular);
        SPO.setFloat("pointLights[0].constant", 1.0f);
        SPO.setFloat("pointLights[0].linear", pntLightLinear);
        SPO.setFloat("pointLights[0].quadratic", pntLightQuadratic);
        // point light 2
        SPO.setVec3("pointLights[1].position", pointLightPositions[1]);
        SPO.setVec3("pointLights[1].ambient", pntLightAmbient);
        SPO.setVec3("pointLights[1].diffuse", pntLightDiffuse);
        SPO.setVec3("pointLights[1].specular", pntLightSpecular);
        SPO.setFloat("pointLights[1].constant", 1.0f);
        SPO.setFloat("pointLights[1].linear", pntLightLinear);
        SPO.setFloat("pointLights[1].quadratic", pntLightQuadratic);
        // point light 3
        SPO.setVec3("pointLights[2].position", pointLightPositions[2]);
        SPO.setVec3("pointLights[2].ambient", pntLightAmbient);
        SPO.setVec3("pointLights[2].diffuse", pntLightDiffuse);
        SPO.setVec3("pointLights[2].specular", pntLightSpecular);
        SPO.setFloat("pointLights[2].constant", 1.0f);
        SPO.setFloat("pointLights[2].linear", pntLightLinear);
        SPO.setFloat("pointLights[2].quadratic", pntLightQuadratic);
        // point light 4
        SPO.setVec3("pointLights[3].position", pointLightPositions[3]);
        SPO.setVec3("pointLights[3].ambient", pntLightAmbient);
        SPO.setVec3("pointLights[3].diffuse", pntLightDiffuse);
        SPO.setVec3("pointLights[3].specular", pntLightSpecular);
        SPO.setFloat("pointLights[3].constant", 1.0f);
        SPO.setFloat("pointLights[3].linear", pntLightLinear);
        SPO.setFloat("pointLights[3].quadratic", pntLightQuadratic);
        // spotLight
        SPO.setVec3("spotLight.position", camera.Position);
        SPO.setVec3("spotLight.direction", camera.Front);
        SPO.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        SPO.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        SPO.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        SPO.setFloat("spotLight.constant", 1.0f);
        SPO.setFloat("spotLight.linear", pntLightLinear);
        SPO.setFloat("spotLight.quadratic", 0.032f);
        SPO.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        SPO.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


		//create projection matrix and send it to _le sáhaader_ 
		glm::mat4 projection = glm::perspective(glm::radians(camera.Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT , 0.1f, 100.0f);
	 	SPO.setMat4("projection", projection);

		//create view matrix and send it to Shaad#1095
		glm::mat4 view = camera.GetViewMatrix();
		SPO.setMat4("view", view);

		SPO.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		SPO.setMat4("model", model);
		testModel.Draw(SPO);


		//bind textures 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, fancyTextureL);
		
		
		B.bindVAO(0);
		for(unsigned int i = 0; i < 16; i++) {

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			//float angle = 20.0f * i + 100 * glfwGetTime() * (i + 1) / 2;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			float angle = 20.0f * i;
    		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			SPO.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

		
		
		//set variables for the second shader 
		LSPO.use();
		LSPO.setVec3("lightColor", glm::vec3(1.0f));
		LSPO.setMat4("projection", projection); //use the same projection matrix
		LSPO.setMat4("view", view); //use the same view matix

		B.bindVAO(1); // bind the VAO 1 
		for(unsigned int i = 0; i < 4; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			//float angle = 20.0f * i + 100 * glfwGetTime() * (i + 1) / 2;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			LSPO.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

	
		
		//check and call 911(events) and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

//init glfw and the main window
GLFWwindow* initWindow(int windowWidth, int windowHeigth, const char* Title) {

	glfwInit(); //init glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //use only core 

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeigth, Title, NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //add the func framebuffer_size_callback to the resize callbacc
	glfwSetCursorPosCallback(window, mouse_callback); //add the cursor position
	glfwSetScrollCallback(window, scroll_callback); //add the scroll callback
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

//init glad
int initGlad(GLFWwindow* window) {

	if (window == NULL) {
		std::cout << "somethings wrong i can feel it" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //make the window the current context 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Glad 2 c that glad failed again" << std::endl;
		return -1;
	}

	return 0;
}


int main() {

	GLFWwindow* window = initWindow(SCR_WIDTH, SCR_HEIGHT, "Help"); //create window

	if (initGlad(window) == -1) { return -1; } //init glad and check window

	glEnable(GL_DEPTH_TEST); //enable depth testing

	glm::mat4 test = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	std::cout << glm::to_string(glm::mat4(1.0f)) << std::endl;

	cout << std::endl;

	//building and compiling shader zone
	Shader SPO("..\\shader\\VertexShader.glsl", "..\\shader\\FragmentShader.glsl");                  //first shader for all normal objs
	Shader LSPO("..\\shader\\VertexShaderLightSrc.glsl", "..\\shader\\FragmentShaderLightSrc.glsl"); //second shader for all light sources
	Model testModel("..\\resources\\backpack\\untitled.fbx");

	//define the vertecies for the cube
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
	};

	Buffer B;

	B.genVAO(0); //generate VAO at array index 0
	B.genVBO(0); //generate VBO at array index 0

	B.bindVBO(0); //bind the VBO at index 0
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //load the vertices into the Vertex Buffer

	B.bindVAO(0); //bind the VAO at index 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //load the position attributes into the Vertex Array 0
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //load the position attributes into the Vertex Array 0
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //load the position attributes into the Vertex Array 0
	glEnableVertexAttribArray(2);

	B.genVAO(1); //generate VAO at array index 1

	B.bindVAO(1); //bind the VAO at array index 1
	B.bindVBO(0); //bind the VBO 0 again; no need to fill it with data as it already contains the vertices, just for educational purposes or something like that i dunno 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //load the position attributes into the Vertex Array 1
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //load the position attributes into the Vertex Array 1
	glEnableVertexAttribArray(1);

	unsigned int diffuseMap = loadTexture("..\\imgs\\container2.png");
	unsigned int specularMap = loadTexture("..\\imgs\\container2_specular.png");
	unsigned int diffuseMapL = loadTexture("..\\imgs\\light.png");

	SPO.use();
	SPO.setInt("material.diffuse", 0);
	SPO.setInt("material.specular", 1);
	LSPO.use();
	LSPO.setInt("fancyTextureL", 2);
	

	renderLoop(window, SPO, LSPO, B, diffuseMap, diffuseMapL, specularMap, testModel); //main renderloop

	glfwTerminate(); //cleanup when done
	return 0;
}