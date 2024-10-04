#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <GLFW/glfw3.h>

class Snake
{
    float tile_size;

public:
    Snake(float tile_size);

    void draw(GLuint shaderProgram, GLuint VAO);
};

#endif // SNAKE_HPP