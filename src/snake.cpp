#include "snake.hpp"
#include "shape.hpp"
#include "constants.hpp"
#include "utils.hpp"

SnakeTile::SnakeTile(Rectangle *rectangle, float tile_size, float tile_height) : tile_size(tile_size), tile_height(tile_height), rectangle(rectangle), next(nullptr)
{
    std::vector<int> grid_reference = this->get_grid_reference(this->rectangle->position);

    this->x_grid_axis = grid_reference[0];
    this->y_grid_axis = grid_reference[1];
};

SnakeTile::~SnakeTile()
{
    if (this->rectangle != nullptr)
    {
        std::cout << "Deleting snake tile rectangle..." << std::endl;
        delete this->rectangle;
    }
}

void SnakeTile::translate_x(float distance)
{
    this->rectangle->translate_x(distance);

    this->x_grid_axis = this->get_single_grid_reference(this->rectangle->position.x, this->tile_size);
}

void SnakeTile::translate_y(float distance)
{
    this->rectangle->translate_y(distance);

    this->y_grid_axis = this->get_single_grid_reference(this->rectangle->position.y, this->tile_height);
}

float SnakeTile::get_x_position()
{
    return this->rectangle->position.x;
}
void SnakeTile::set_x_position(float new_position)
{
    this->rectangle->position.x = new_position;

    this->x_grid_axis = this->get_single_grid_reference(this->rectangle->position.x, this->tile_size);
}

float SnakeTile::get_y_position()
{
    return this->rectangle->position.y;
}
void SnakeTile::set_y_position(float new_position)
{
    this->rectangle->position.y = new_position;

    this->y_grid_axis = this->get_single_grid_reference(this->rectangle->position.y, this->tile_height);
}

int SnakeTile::get_x_grid_axis()
{
    return this->x_grid_axis;
}
int SnakeTile::get_y_grid_axis()
{
    return this->y_grid_axis;
}

void SnakeTile::draw(GLuint shaderProgram, GLuint VAO)
{
    this->rectangle->draw(shaderProgram, VAO);
};

int SnakeTile::get_single_grid_reference(float coordinate, float grid_width)
{
    float res = (coordinate + 1 + (grid_width / 2)) / (2.0 / Dimensions::grid_axis_count);

    return std::round(res);
}

std::vector<int> SnakeTile::get_grid_reference(glm::vec2 coordinates)
{
    std::vector<int> res = {
        this->get_single_grid_reference(coordinates.x, this->tile_size),
        this->get_single_grid_reference(coordinates.y, this->tile_height)};

    return res;
}

float Snake::get_single_coordinate(int grid_axis, float grid_width)
{
    // following the function -> -1.1 + x * (2 / grids_count) = y
    float res = -1 - (grid_width / 2) + grid_axis * (2.0 / Dimensions::grid_axis_count);

    return res;
}

glm::vec2 Snake::get_coordinates(int x_grid_axis, int y_grid_axis)
{
    glm::vec2 res = glm::vec2(this->get_single_coordinate(x_grid_axis, this->tile_size), this->get_single_coordinate(y_grid_axis, this->tile_height));

    return res;
}

void Snake::draw_apple(GLuint shaderProgram, GLuint VAO)
{
    if (this->apple != nullptr)
        this->apple->draw(shaderProgram, VAO);
}

bool Snake::check_snake_collision(SnakeTile *snake_head)
{
    SnakeTile *current = this->head_tile;

    while (current != nullptr)
    {
        // this will get all tiles except for the last one, which is the head of the snake
        if (current->next == nullptr)
            break;

        int x_positions_difference = snake_head->get_x_grid_axis() - current->get_x_grid_axis();
        int y_positions_difference = snake_head->get_y_grid_axis() - current->get_y_grid_axis();

        if (y_positions_difference == 0 && x_positions_difference == 0)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool Snake::check_border_collision(SnakeTile *snake_head)
{
    if (snake_head->get_x_grid_axis() <= 0 || snake_head->get_x_grid_axis() > Dimensions::grid_axis_count || snake_head->get_y_grid_axis() <= 0 || snake_head->get_y_grid_axis() > Dimensions::grid_axis_count)
    {
        return true;
    }

    return false;
}

void Snake::insert_tile(SnakeTile *new_tile)
{
    new_tile->next = this->head_tile;
    this->head_tile = new_tile;
}

void Snake::reset()
{
    this->delete_snake();
    this->create_initial_snake();
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
            current->set_x_position(current->next->get_x_position());
            current->set_y_position(current->next->get_y_position());
        }

        current->draw(shaderProgram, VAO);

        last_tile = current;
        current = current->next;
    }

    if (this->current_tile_position >= this->tile_size && last_tile != nullptr)
    {
        this->current_tile_position = 0.0f;

        switch (this->current_direction)
        {
        case SNAKE_DIRECTION_LEFT:
            last_tile->translate_x(-1 * this->tile_size);
            break;
        case SNAKE_DIRECTION_RIGHT:
            last_tile->translate_x(this->tile_size);
            break;
        case SNAKE_DIRECTION_UP:
            last_tile->translate_y(this->tile_size);
            break;
        case SNAKE_DIRECTION_DOWN:
            last_tile->translate_y(-1 * this->tile_size);
            break;
        default:
            break;
        }

        if (this->check_snake_collision(last_tile))
        {
            this->play = false;
        }

        if (this->check_border_collision(last_tile))
        {
            // GAME OVER!!!
            this->play = false;
        }
    }

    this->draw_apple(shaderProgram, VAO);
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

    if (glfwGetKey(this->window, GLFW_KEY_R) == GLFW_PRESS)
    {
        this->reset();
    }

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

void Snake::create_initial_snake()
{
    this->tile_height = tile_size / 1.5f;

    for (int i = 0; i < this->initial_tile_count; i++)
    {
        float tile_x_position = (this->tile_size / -2) + (this->tile_size * i);

        glm::vec2 position(tile_x_position, this->tile_height);
        glm::vec2 size(this->tile_size, this->tile_height);
        Rectangle *rectangle = new Rectangle(position, size, Colors::green);

        SnakeTile *current_tile = new SnakeTile(rectangle, this->tile_size, this->tile_height);
        this->insert_tile(current_tile);
    }
}

void Snake::delete_snake()
{
    std::cout << "Deleting Snake tiles..." << std::endl;

    SnakeTile *current = this->head_tile;

    while (current != nullptr)
    {
        SnakeTile *nextNode = current->next;

        delete current; // Free the memory
        current = nextNode;
    }

    if (this->apple != nullptr)
    {
        delete this->apple;
    }

    this->head_tile = nullptr;
    this->apple = nullptr;
}

Snake::Snake(GLFWwindow *window, float tile_size) : window(window), play(false), speed(0.005f), current_tile_position(0.0f), current_direction(SNAKE_DIRECTION_LEFT), initial_tile_count(5), tile_size(tile_size), head_tile(nullptr), apple(nullptr)
{
    this->create_initial_snake();

    const int random_x_number = Utils::get_random_integer(1, Dimensions::grid_axis_count);
    const int random_y_number = Utils::get_random_integer(1, Dimensions::grid_axis_count);

    glm::vec2 apple_coordinates = this->get_coordinates(random_x_number, random_y_number);
    glm::vec2 apple_size(this->tile_size, this->tile_height);

    this->apple = new Rectangle(apple_coordinates, apple_size, Colors::red);
}

Snake::~Snake()
{
    this->delete_snake();
}