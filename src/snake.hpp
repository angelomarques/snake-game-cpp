#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

class SnakeTile
{
public:
    SnakeTile *next;

    float x_position;
    float y_position;

    SnakeTile(float x_position, float y_position);
};

class Snake
{
    float tile_size;
    float tile_height;
    SnakeTile *head_tile;

public:
    Snake(float tile_size);

    void draw(GLuint shaderProgram, GLuint VAO);

    void insert_tile(SnakeTile *tile);

    ~Snake();
};

#endif // SNAKE_HPP