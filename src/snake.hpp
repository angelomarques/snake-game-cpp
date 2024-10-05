#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "shape.hpp"

class SnakeTile
{
public:
    SnakeTile *next;
    Rectangle *rectangle;

    float x_position;
    float y_position;

    SnakeTile(float x_position, float y_position, Rectangle *rectangle);
};

class Snake
{
    GLFWwindow *window;
    bool play;
    float speed;

    int initial_tile_count;
    float tile_size;
    float tile_height;

    SnakeTile *head_tile;

public:
    Snake(GLFWwindow *window, float tile_size);

    void draw(GLuint shaderProgram, GLuint VAO);

    void insert_tile(SnakeTile *tile);

    void processInput();

    ~Snake();
};

#endif // SNAKE_HPP