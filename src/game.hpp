#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shader.hpp"

class Rectangle
{
    glm::vec2 position;
    glm::vec2 size;

public:
    Rectangle(const glm::vec2 &position, const glm::vec2 &size);

    void draw(GLuint shaderProgram, GLuint VAO);

    void translate_x(float distance);
    void translate_y(float distance);
};

class Game
{
private:
    GLFWwindow *window;

    GLuint VAO,
        VBO, EBO;
    Shader shader;
    std::string name;

    float pos_x, pos_y;

    void processInput();

    std::vector<Rectangle> rectangles; // Vector to store rectangles

    int selectedRect = -1; // Track which rectangle is selected

public:
    Game(GLFWwindow *window);

    void render();

    ~Game();
};

#endif // GAME_HPP
