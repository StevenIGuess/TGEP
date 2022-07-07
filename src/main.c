#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// public varibales, that define the initial staring values will be declared here
#include "settings.h"
// general functions like initWindow() and for callbacc functions
#include "helper.h"
// functions for creating shader
#include "shader.h"
// handle events like input
#include "eventHandler.h"
// load textures
#include "textureLoader.h"
#include "vectorcalc.h"
// vector math

float lastFrame = 0.0f;
float deltaTime = 0.0f;
float currentFrame;
float pos1 = 0.0f;
float pos2 = 0.0f;
float speedOfLightLol = 0.01f;

struct BufferArray
{
    unsigned int ID;
};

struct CameraData
{
    vec3 Position;
    vec3 Front;
    vec3 FrontMove;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    // euler angles, this needs to be swapped for quaternions
    float Yaw, Pitch;
    // cameraSettings
    float MovementSpeed, MouseSensitivity, Fov;
};

void genBuffers(struct BufferArray *VBOs, struct BufferArray *VAOs)
{

    for (int i = 0; i < sizeof(VAOs) / sizeof(struct BufferArray); i++)
    {
        printf("%s%i\n", "Iteration of VAO::", i);
        glGenVertexArrays(1, &VAOs[i].ID);
    }

    for (int i = 0; i < sizeof(VBOs) / sizeof(struct BufferArray); i++)
    {
        printf("%s%i\n", "Iteration of VBO::", i);
        glGenBuffers(1, &VBOs[i].ID);
    }
}

int main()
{

    GLFWwindow *window = initWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE);

    if (initGlad(window) == -1)
    {
        return -1;
    }

    mat4 view = lookAtMatrix(Vector3(0.0f, 0.0f, 3.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));

    printf("Both::\n");
    printM4(view);

    /*

    unsigned int shaderProgram = compileShader("..\\Shader\\Vertex\\VertexShader.glsl", "..\\Shader\\Fragment\\FragmentShader.glsl");
    unsigned int shaderProgram1 = compileShader("..\\Shader\\Vertex\\VertexShader1.glsl", "..\\Shader\\Fragment\\FragmentShader1.glsl");

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

    struct BufferArray *VBOs = malloc(sizeof(struct BufferArray) * 1);
    struct BufferArray *VAOs = malloc(sizeof(struct BufferArray) * 2);
    genBuffers(VBOs, VAOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0].ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VBOs[0].ID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAOs[1].ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0].ID);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int diffuseMap = loadTexture("..\\imgs\\container2.png");
    unsigned int specularMap = loadTexture("..\\imgs\\container2_specular.png");
    unsigned int diffuseMapL = loadTexture("..\\imgs\\light.png");

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.specular"), 1);
    glUseProgram(shaderProgram1);
    glUniform1i(glGetUniformLocation(shaderProgram1, "fancyTextureL"), 2);

    struct CameraData *cameraData = malloc(sizeof(struct CameraData));

    cameraData->Position = Vector3(0.0f, 0.0f, 3.0f);
    cameraData->WorldUp  = Vector3(0.0f, 1.0f, 0.0f);
    cameraData->Yaw = radians(0.0f);
    cameraData->Pitch = radians(0.0f);


    while (!glfwWindowShouldClose(window))
    {

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //input
        processKeyboardEvents(window);

        //background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[1].ID);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    printf("%s", "Hello, World!");


    glDeleteVertexArrays(1, &VAOs[1].ID);
    glDeleteBuffers(1, &VBOs[1].ID);
    glDeleteProgram(shaderProgram);

    free(VBOs);
    free(VAOs);
    */

    glfwTerminate();
    return 0;
}