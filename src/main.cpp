#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"
#include "shader.h"
#include "texture.h"
#include "buffers.h"

void renderingLoop(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char WINDOW_TITLE[] = "LearnOpenGL";

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
    Texture texture("src/textures/wall.jpg");
    float offset = -0.7f;
    shader.setFloat("xOffset", offset);

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
