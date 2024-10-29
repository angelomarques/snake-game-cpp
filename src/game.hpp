#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>
#include "shader.hpp"
#include "shape.hpp"
#include "layout.hpp"
#include "snake.hpp"
#include "text.hpp"

class InfoScreenText
{
public:
    std::string title;
    std::string subtitle;

    float title_x;
    float title_y;

    float subtitle_x;
    float subtitle_y;

    // Default constructor
    InfoScreenText() : title(""), subtitle(""), title_x(0), title_y(0), subtitle_x(0), subtitle_y(0) {}

    InfoScreenText(std::string title, std::string subtitle, float title_x, float title_y, float subtitle_x, float subtitle_y);
};

enum class InfoScreenTextType
{
    Welcome,
    GameOver,
    Paused
};

class InfoScreen
{
private:
    GLuint VAO;
    GLuint main_shader_program;
    Text text_context;
    Rectangle *overlay;
    bool hidden;

    InfoScreenTextType text_type;

    std::unordered_map<InfoScreenTextType, InfoScreenText> texts = {};

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
