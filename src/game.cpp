#include "game.hpp"
#include "shader.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Game::render()
{

    // Use the shader program
    glUseProgram(this->shader.get_shader_program());

    // Bind VAO and draw the square using the element array
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Game::Game(std::string name) : shader("src/shaders/vertex_shader.glsl", "src/shaders/fragment_shader.glsl"), name(name)
{
    // Define square vertices (two triangles to form a square)
    float vertices[] = {
        // positions
        -0.5f, -1.0f, // bottom left
        0.5f, -1.0f,  // bottom right
        0.5f, 0.5f,   // top right
        -0.5f, 0.5f   // top left
    };

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    // Create VAO, VBO, and EBO
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Game::~Game()
{
    std::cout << "Destroying Buffers (VAO, VBO, EBO)..." << std::endl;
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}
