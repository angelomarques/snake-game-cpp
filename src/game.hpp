#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"

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

public:
    Game(GLFWwindow *window);

    void render();

    ~Game();
};

#endif // GAME_HPP
