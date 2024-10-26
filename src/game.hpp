#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "shader.hpp"
#include "shape.hpp"
#include "layout.hpp"
#include "snake.hpp"
#include "text.hpp"

class InfoScreen
{
private:
    GLuint VAO;
    GLuint main_shader_program;
    Text text_context;
    Rectangle *overlay;
    bool hidden;

public:
    InfoScreen(GLuint VAO, GLuint main_shader_program);

    void draw();

    void hide();
};

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

    InfoScreen *info_screen;

    void processInput();

public:
    Game(GLFWwindow *window);

    void render();

    ~Game();
};

#endif // GAME_HPP
