#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

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
