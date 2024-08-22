#include <glad/glad.h>

#include "buffers.h"

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
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
    // // Bind VAO
    glBindVertexArray(VAO);

    // Vertex Attribs
    unsigned int vertexSize = 8 * sizeof(float);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return VAO;
}

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
unsigned int EBOInit()
{
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return EBO;
}