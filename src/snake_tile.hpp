#ifndef SNAKE_TILE_HPP
#define SNAKE_TILE_HPP

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
    int direction;
    std::vector<Rectangle> borders = {};
    std::vector<bool> border_reference; // {top, right, bottom, left}
    bool has_borders = true;
    std::vector<Rectangle> eyes = {};

    int x_grid_axis = 0;
    int y_grid_axis = 0;

    float border_width = 0.005f;
    float eye_width = 0.01f;
    float eye_height = 0.015f;

    std::vector<int> get_grid_reference(glm::vec2 coordinates);

    int get_single_grid_reference(float coordinate, float grid_width);

    void set_borders();

    Rectangle get_new_border(int location);

    void set_eyes_position();

public:
    SnakeTile *next;
    SnakeTile *previous;

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

    void set_direction(int new_direction);
    int get_direction();

    void set_new_borders();

    void set_has_borders(bool has_borders);

    void create_eyes();

    ~SnakeTile();
};

#endif // SNAKE_TILE_HPP