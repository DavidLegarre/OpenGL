#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"

void renderingLoop(GLFWwindow *window);
unsigned int VBOInit();
unsigned int VAOInit();
int createShaderProgram();
enum Shader {VERTEX_SHADER, FRAGMENT_SHADER};
int compileShader(enum Shader shaderType);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char WINDOW_TITLE[] = "LearnOpenGL";

const char *vertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;"
    "void main()"
    "{"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
    "}";

const char *fragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;"
    "void main()"
    "{"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}";

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};


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
    // Vertex Attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    unsigned int shaderProgram = createShaderProgram();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
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

    return VAO;
}

int createShaderProgram()
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // Compile the shaders for the program
    unsigned int vertexShader = compileShader(VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(FRAGMENT_SHADER);
    // Attach shaders to program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link shader program
    glLinkProgram(shaderProgram);

    // Delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int compileShader(enum Shader shaderType)
{
    // Create the Shader
    unsigned int shader;
    const char *shaderSource;
    switch (shaderType) {
        case VERTEX_SHADER:
            shader = glCreateShader(GL_VERTEX_SHADER);
            shaderSource = vertexShaderSource;
            break;
        case FRAGMENT_SHADER:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            shaderSource = fragmentShaderSource;
            break;
        default:
            throw std::runtime_error("Invalid fragment type"); // Throw an exception
            break;

    }
    // Attach the shader source code
    glShaderSource(shader, 1, &shaderSource, nullptr);
    // Compile shader source
    glCompileShader(shader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    return shader;
}