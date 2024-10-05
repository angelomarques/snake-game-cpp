#include "game.hpp"
#include "shader.hpp"
#include "constants.hpp"
#include <iostream>

void Game::render()
{

    // Clear the screen with a black color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the shader program
    glUseProgram(this->shader.get_shader_program());

    main_layout.draw(this->shader.get_shader_program(), VAO);

    this->snake.processInput();
    snake.draw(this->shader.get_shader_program(), this->VAO);
}

Game::Game(GLFWwindow *window) : window(window), main_layout(Dimensions::grid_axis_count, Dimensions::grid_axis_count), snake(window, Dimensions::total_width / Dimensions::grid_axis_count), shader("src/shaders/vertex_shader.glsl", "src/shaders/fragment_shader.glsl"), pos_x(0.0f), pos_y(0.0f)
{
    // Define square vertices (two triangles to form a square)
    float vertices[] = {
        // first rectangle coordinates
        -0.5f, -1.0f, // bottom left
        0.5f, -1.0f,  // bottom right
        0.5f, 0.5f,   // top right
        -0.5f, 0.5f,  // top left
    };

    unsigned int indices[] = {
        // First square
        0, 1, 2, // First triangle
        2, 3, 0, // Second triangle
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

    this->rectangles = {};
}

Game::~Game()
{
    std::cout << "Destroying Buffers (VAO, VBO, EBO)..." << std::endl;
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}
