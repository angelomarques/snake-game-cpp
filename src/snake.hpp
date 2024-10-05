#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <GLFW/glfw3.h>
class SnakeTile
{
public:
    SnakeTile *next;
    SnakeTile();
};

class Snake
{
    float tile_size;
    SnakeTile *head_tile;

public:
    Snake(float tile_size);

    void draw(GLuint shaderProgram, GLuint VAO);

    void insert_tile(SnakeTile *tile);
};

#endif // SNAKE_HPP