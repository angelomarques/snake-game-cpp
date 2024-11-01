#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include "shape.hpp"
#include "snake_tile.hpp"

class Snake
{
    GLFWwindow *window;
    bool is_playing;
    bool is_game_over;
    float speed;
    float current_tile_position;
    int current_direction;

    int initial_tile_count;
    float tile_size;
    float tile_height;

    SnakeTile *head_tile;
    SnakeTile *apple;

    std::vector<std::vector<int>> available_grids;

    std::queue<int> inputs_queue;

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

    void on_direction_change(int direction);

    void play();
    bool get_is_game_over();

    void reset();

    bool get_is_playing();
    void set_is_playing(bool is_playing);

    ~Snake();
};

#endif // SNAKE_HPP