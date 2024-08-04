#include <glad/glad.h>

#include "buffers.h"

float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
};

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