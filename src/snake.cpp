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
    SnakeTile *last_tile = current; // The last tile is actually the "head" of the snake

    if (this->play == true)
    {
        this->current_tile_position += speed;
    }

    while (current != nullptr)
    {
        if (this->current_tile_position >= this->tile_size && current->next != nullptr)
        {
            current->rectangle->position.x = current->next->rectangle->position.x;
            current->rectangle->position.y = current->next->rectangle->position.y;
        }

        current->rectangle->draw(shaderProgram, VAO);

        last_tile = current;
        current = current->next;
    }

    if (this->current_tile_position >= this->tile_size && last_tile != nullptr)
    {
        this->current_tile_position = 0.0f;

        switch (this->current_direction)
        {
        case SNAKE_DIRECTION_LEFT:
            last_tile->rectangle->translate_x(-1 * this->tile_size);
            break;
        case SNAKE_DIRECTION_RIGHT:
            last_tile->rectangle->translate_x(this->tile_size);
            break;
        case SNAKE_DIRECTION_UP:
            last_tile->rectangle->translate_y(this->tile_size);
            break;
        case SNAKE_DIRECTION_DOWN:
            last_tile->rectangle->translate_y(-1 * this->tile_size);
            break;
        default:
            break;
        }

        float new_head_x_position = last_tile->rectangle->position.x;
        float new_head_y_position = last_tile->rectangle->position.y;

        switch (this->current_direction)
        {
        case SNAKE_DIRECTION_LEFT:
            new_head_x_position -= this->tile_size;
            break;
        case SNAKE_DIRECTION_RIGHT:
            new_head_x_position += this->tile_size;
            break;
        case SNAKE_DIRECTION_UP:
            new_head_y_position += this->tile_size;
            break;
        case SNAKE_DIRECTION_DOWN:
            new_head_y_position -= this->tile_size;
            break;
        default:
            break;
        }

        if (new_head_x_position >= Dimensions::positive_border_coordinate || new_head_x_position <= Dimensions::negative_border_coordinate || new_head_y_position >= Dimensions::positive_border_coordinate || new_head_y_position <= Dimensions::negative_border_coordinate)
        {
            // GAME OVER!!!
            this->play = false;
        }
    }
}

void Snake::processInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        // The SPACE is treated as "play" button
        this->play = true;
    }
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // The SPACE is treated as "play" button
        this->play = false;
    }

    // if (glfwGetKey(this->window, GLFW_KEY_R) == GLFW_PRESS)
    // {
    //     this->reset();
    // }

    if (this->head_tile != nullptr)
    {
        if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            this->current_direction = SNAKE_DIRECTION_LEFT;
        }
        if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            this->current_direction = SNAKE_DIRECTION_RIGHT;
        }
        if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            this->current_direction = SNAKE_DIRECTION_UP;
        }
        if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            this->current_direction = SNAKE_DIRECTION_DOWN;
        }
    }
}

Snake::Snake(GLFWwindow *window, float tile_size) : window(window), play(false), speed(0.005f), current_tile_position(0.0f), current_direction(SNAKE_DIRECTION_LEFT), initial_tile_count(5), tile_size(tile_size), head_tile(nullptr)
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