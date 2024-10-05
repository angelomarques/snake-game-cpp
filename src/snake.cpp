#include "snake.hpp"
#include "shape.hpp"
#include "constants.hpp"

SnakeTile::SnakeTile(float x_position, float y_position) : next(nullptr), x_position(x_position), y_position(y_position) {};

void Snake::insert_tile(SnakeTile *new_tile)
{
    new_tile->next = this->head_tile;
    this->head_tile = new_tile;
}

void Snake::draw(GLuint shaderProgram, GLuint VAO)
{
    SnakeTile *current = this->head_tile;

    while (current != nullptr)
    {
        glm::vec2 position(current->x_position, current->y_position);
        glm::vec2 size(this->tile_size, this->tile_height);
        Rectangle rectangle(position, size, Colors::green);
        rectangle.draw(shaderProgram, VAO);

        current = current->next;
    }
}

Snake::Snake(float tile_size) : tile_size(tile_size), head_tile(nullptr)
{
    this->tile_height = tile_size / 1.5f;

    SnakeTile *first_tile = new SnakeTile(this->tile_size / -2, this->tile_height);
    this->insert_tile(first_tile);
}

Snake::~Snake()
{
    std::cout << "Deleting Snake tiles..." << std::endl;

    SnakeTile *current = this->head_tile;

    while (current != nullptr)
    {
        SnakeTile *nextNode = current->next;

        delete current; // Free the memory
        current = nextNode;
    }
}