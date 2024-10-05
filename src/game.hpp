#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "shader.hpp"
#include "shape.hpp"
#include "layout.hpp"
#include "snake.hpp"

class Game
{
private:
    GLFWwindow *window;
    GridLayout main_layout;
    Snake snake;

    GLuint VAO,
        VBO, EBO;
    Shader shader;
    std::string name;

    float pos_x, pos_y;

    std::vector<Rectangle> rectangles; // Vector to store rectangles

    int selectedRect = -1; // Track which rectangle is selected

public:
    Game(GLFWwindow *window);

    void render();

    ~Game();
};

#endif // GAME_HPP
