#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#include "shape.hpp"

const int SNAKE_DIRECTION_UP = 0;
const int SNAKE_DIRECTION_DOWN = 1;
const int SNAKE_DIRECTION_LEFT = 2;
const int SNAKE_DIRECTION_RIGHT = 3;

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
    float current_tile_position;
    int current_direction;

    int initial_tile_count;
    float tile_size;
    float tile_height;

    SnakeTile *head_tile;

    void reset();

    void insert_tile(SnakeTile *tile);

    void create_initial_snake();

    void delete_snake();

    bool check_snake_collision(glm::vec2 new_head_position);

    void draw_apple(GLuint shaderProgram, GLuint VAO);

public:
    Snake(GLFWwindow *window, float tile_size);

    void draw(GLuint shaderProgram, GLuint VAO);

    void processInput();

    ~Snake();
};

#endif // SNAKE_HPP