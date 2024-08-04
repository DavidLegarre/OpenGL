#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"
#include "shader.h"

void renderingLoop(GLFWwindow *window);
unsigned int VBOInit();
unsigned int VAOInit();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char WINDOW_TITLE[] = "LearnOpenGL";

float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
};

int main()
{
    GLFWwindow *window = initWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE);
    // Window Loop
    renderingLoop(window);
    glfwTerminate();
    return 0;
}

void renderingLoop(GLFWwindow *window)
{
    unsigned int VBO = VBOInit();
    unsigned int VAO = VAOInit();
    Shader shader("src/shaders/shader.vs", "src/shaders/shader.fs");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

unsigned int VBOInit()
{
    // Defines and initializes the Vertex Buffer Object (VBO)
    // Define VBO id
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the data for the VBO
    // Copying the vertices float array object into VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    return VBO;
}

unsigned int VAOInit()
{
    // Inits Vertex Array Object (VAO)
    // The VAO specifies how to read the data in the VBO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // Bind VAO
    glBindVertexArray(VAO);
    // Vertex Attrib
    unsigned int vertexSize = 6 * sizeof(float);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void *)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}
