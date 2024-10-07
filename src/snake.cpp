#include "snake.hpp"
#include "shape.hpp"
#include "constants.hpp"

SnakeTile::SnakeTile(float x_position, float y_position, Rectangle *rectangle) : next(nullptr), rectangle(rectangle), x_position(x_position), y_position(y_position) {};

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

        current->rectangle->draw(shaderProgram, VAO);

        if (this->play == true)
        {
            current->rectangle->translate_x(-1 * this->speed);
        }

        current = current->next;
    }
}

void Snake::processInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        // The SPACE is treated as "play" button
        this->play = true;
    }

    if (this->head_tile != nullptr)
    {
        if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            this->head_tile->rectangle->translate_x(-1 * (this->tile_size / 4));
        }
        if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            this->head_tile->rectangle->translate_x(this->tile_size / 4);
        }
        if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            this->head_tile->rectangle->translate_y(this->tile_size / 4);
        }
        if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            this->head_tile->rectangle->translate_y(-1 * (this->tile_size / 4));
        }
    }
}

Snake::Snake(GLFWwindow *window, float tile_size) : window(window), play(false), speed(0.005f), initial_tile_count(5), tile_size(tile_size), head_tile(nullptr)
{
    this->tile_height = tile_size / 1.5f;

    for (int i = 0; i < this->initial_tile_count; i++)
    {
        float tile_x_position = (this->tile_size / -2) + (this->tile_size * i);

        glm::vec2 position(tile_x_position, this->tile_height);
        glm::vec2 size(this->tile_size, this->tile_height);
        Rectangle *rectangle = new Rectangle(position, size, Colors::green);

        SnakeTile *first_tile = new SnakeTile(tile_x_position, this->tile_height, rectangle);
        this->insert_tile(first_tile);
    }
}

Snake::~Snake()
{
    std::cout << "Deleting Snake tiles..." << std::endl;

    SnakeTile *current = this->head_tile;

    while (current != nullptr)
    {
        SnakeTile *nextNode = current->next;

        delete current->rectangle;
        delete current; // Free the memory
        current = nextNode;
    }
}