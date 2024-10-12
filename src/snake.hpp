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
    Rectangle *rectangle;

    int x_grid_axis = 0;
    int y_grid_axis = 0;

    std::vector<int> get_grid_reference(glm::vec2 coordinates);

    int get_single_grid_reference(float coordinate, float grid_width);

public:
    SnakeTile *next;

    SnakeTile(Rectangle *rectangle, float tile_size, float tile_height);

    void draw(GLuint shaderProgram, GLuint VAO);

    // Getters and Setters:
    float get_x_position();
    void set_x_position(float new_position);

    float get_y_position();
    void set_y_position(float new_position);

    int get_x_grid_axis();
    int get_y_grid_axis();

    void translate_x(float distance);
    void translate_y(float distance);

    ~SnakeTile();
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
    SnakeTile *apple;

    std::vector<std::vector<int>> available_grids;

    void reset();

    void insert_tile(SnakeTile *tile);

    void create_initial_snake();

    void delete_snake();

    bool check_snake_collision(SnakeTile *snake_head);
    bool check_border_collision(SnakeTile *snake_head);
    bool check_apple_collision(SnakeTile *snake_head);

    void draw_apple(GLuint shaderProgram, GLuint VAO);

    glm::vec2 get_coordinates(int x_grid_axis, int y_grid_axis);

    float get_single_coordinate(int grid_axis, float grid_width);

    void remove_available_grid_coordinate_pair(int x, int y);
    void add_available_grid_coordinate_pair(int x, int y);

    std::vector<int> get_random_available_grid();

    void set_new_apple();

public:
    Snake(GLFWwindow *window, float tile_size);

    void draw(GLuint shaderProgram, GLuint VAO);

    void processInput();

    ~Snake();
};

#endif // SNAKE_HPP