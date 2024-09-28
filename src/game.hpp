#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"

class Game
{
private:
    GLuint VAO, VBO, EBO;
    Shader shader;
    std::string name;

public:
    Game(std::string name);

    void render();

    ~Game();
};

#endif // GAME_HPP
