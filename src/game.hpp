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

    std::string title;
    std::string subtitle;

    float title_x;
    float title_y;

    float subtitle_x;
    float subtitle_y;

public:
    InfoScreen(GLuint VAO, GLuint main_shader_program);
    ~InfoScreen();

    void draw();

    void hide();

    void set_game_over();
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
