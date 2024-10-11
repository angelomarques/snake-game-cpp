#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "shape.hpp"

const int SNAKE_DIRECTION_UP = 0;
const int SNAKE_DIRECTION_DOWN = 1;
const int SNAKE_DIRECTION_LEFT = 2;
const int SNAKE_DIRECTION_RIGHT = 3;

class SnakeTile
{
    float tile_size;
    float tile_height;

    std::vector<int> get_grid_reference(glm::vec2 coordinates);

    int get_single_grid_reference(float coordinate, float grid_width);

public:
    SnakeTile *next;
    Rectangle *rectangle;

    int x_grid_axis = 0;
    int y_grid_axis = 0;

    SnakeTile(Rectangle *rectangle, float tile_size, float tile_height);
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
    Rectangle *apple;

    void reset();

    void insert_tile(SnakeTile *tile);

    void create_initial_snake();

    void delete_snake();

    bool check_snake_collision(glm::vec2 new_head_position);

    void draw_apple(GLuint shaderProgram, GLuint VAO);

    glm::vec2 get_coordinates(int x_grid_axis, int y_grid_axis);

    float get_single_coordinate(int grid_axis, float grid_width);

public:
    Snake(GLFWwindow *window, float tile_size);

    void draw(GLuint shaderProgram, GLuint VAO);

    void processInput();

    ~Snake();
};

#endif // SNAKE_HPP