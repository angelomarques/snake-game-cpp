#include "snake.hpp"

SnakeTile::SnakeTile() : next(nullptr) {};

void Snake::insert_tile(SnakeTile *tile)
{
    SnakeTile *new_tile = new SnakeTile();
    new_tile->next = this->head_tile;
    this->head_tile = new_tile;
}

void Snake::draw(GLuint shaderProgram, GLuint VAO)
{
    // int horizontal_lines_count = this->vertical + 1;
    // float horizontal_lines_threshold = Dimensions::total_width / this->vertical;

    // for (int i = 0; i < horizontal_lines_count; i++)
    // {
    //     float y_position = 1.0f - (horizontal_lines_threshold * i);

    //     glm::vec2 horizontal_line_position(0.0f, y_position);
    //     glm::vec2 horizontal_line_size(Dimensions::total_width, this->line_width);
    //     Rectangle horizontal_line(horizontal_line_position, horizontal_line_size, this->line_color);
    //     horizontal_line.draw(shaderProgram, VAO);
    // }

    // int vertical_lines_count = this->horizontal + 1;
    // float vertical_lines_threshold = Dimensions::total_width / this->horizontal;

    // for (int i = 0; i < vertical_lines_count; i++)
    // {
    //     float x_position = 1.0f - (vertical_lines_threshold * i);

    //     glm::vec2 vertical_line_position(x_position, 0.0f);
    //     glm::vec2 vertical_line_size(this->line_width, Dimensions::total_width);
    //     Rectangle vertical_line(vertical_line_position, vertical_line_size, this->line_color);
    //     vertical_line.draw(shaderProgram, VAO);
    // }
}

Snake::Snake(float tile_size) : tile_size(tile_size), head_tile(nullptr)
{
    SnakeTile *first_tile = new SnakeTile();
    this->insert_tile(first_tile);
}