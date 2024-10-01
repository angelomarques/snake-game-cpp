#include "game.hpp"
#include "shader.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Rectangle::draw(GLuint shaderProgram, GLuint VAO)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->position, 0.0f));
    model = glm::scale(model, glm::vec3(this->size, 1.0f));

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Game::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        // Add a new rectangle when SPACE is pressed
        Rectangle newRect;
        newRect.position = glm::vec2(0.0f, 0.0f);
        newRect.size = glm::vec2(0.2f, 0.2f);
        this->rectangles.push_back(newRect);
        selectedRect = this->rectangles.size() - 1; // Select the newly added rectangle
    }

    if (selectedRect >= 0)
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            this->rectangles[selectedRect].position.x -= 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            this->rectangles[selectedRect].position.x += 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            this->rectangles[selectedRect].position.y += 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            this->rectangles[selectedRect].position.y -= 0.01f;
        }
    }
}

void Game::render()
{
    this->processInput();

    // Clear the screen with a black color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the shader program
    glUseProgram(this->shader.get_shader_program());

    // // Apply the transformation (translation) to move the square
    // glm::mat4 transform = glm::mat4(1.0f); // Identity matrix
    // transform = glm::translate(transform, glm::vec3(this->pos_x, this->pos_y, 0.0f));

    // // Send the transformation to the vertex shader
    // GLuint transformLoc = glGetUniformLocation(this->shader.get_shader_program(), "transform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // // Bind VAO and draw the square using the element array
    // glBindVertexArray(this->VAO);
    // glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    for (auto &rect : rectangles)
    {
        rect.draw(this->shader.get_shader_program(), VAO);
    }
}

Game::Game(GLFWwindow *window) : window(window), shader("src/shaders/vertex_shader.glsl", "src/shaders/fragment_shader.glsl"), pos_x(0.0f), pos_y(0.0f)
{
    // Define square vertices (two triangles to form a square)
    float vertices[] = {
        // first rectangle coordinates
        -0.5f, -1.0f, // bottom left
        0.5f, -1.0f,  // bottom right
        0.5f, 0.5f,   // top right
        -0.5f, 0.5f,  // top left

        // second rectangle coordinates
        0.75f, -1.0f, // bottom left
        0.85f, -1.0f, // bottom right
        0.85f, 0.5f,  // top right
        0.75f, 0.5f   // top left
    };

    unsigned int indices[] = {
        // First square
        0, 1, 2, // First triangle
        2, 3, 0, // Second triangle

        // Second square
        4, 5, 6, // First triangle
        6, 7, 4  // Second triangle
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
