#include "snake.hpp"
#include "shape.hpp"
#include "constants.hpp"
#include "utils.hpp"

bool Snake::get_is_playing()
{
    return this->is_playing;
}

void Snake::set_is_playing(bool is_playing)
{
    this->is_playing = is_playing;
}

bool Snake::get_is_game_over()
{
    return this->is_game_over;
}

void Snake::play()
{
    this->is_playing = true;
}

void Snake::set_new_apple()
{
    glm::vec2 new_tile_position(this->head_tile->get_x_position(), this->head_tile->get_y_position());
    int new_tile_direction = SNAKE_DIRECTION_LEFT;

    switch (this->head_tile->get_direction())
    {
    case SNAKE_DIRECTION_LEFT:
        new_tile_direction = SNAKE_DIRECTION_LEFT;
        new_tile_position.x = this->head_tile->get_x_position() + this->tile_size;
        break;
    case SNAKE_DIRECTION_RIGHT:
        new_tile_direction = SNAKE_DIRECTION_RIGHT;
        new_tile_position.x = this->head_tile->get_x_position() - this->tile_size;
        break;
    case SNAKE_DIRECTION_UP:
        new_tile_direction = SNAKE_DIRECTION_UP;
        new_tile_position.y = this->head_tile->get_y_position() - this->tile_size;
        break;
    case SNAKE_DIRECTION_DOWN:
        new_tile_direction = SNAKE_DIRECTION_DOWN;
        new_tile_position.y = this->head_tile->get_y_position() + this->tile_size;
        break;
    default:
        break;
    }

    glm::vec2 size(this->tile_size, this->tile_height);
    Rectangle *rectangle = new Rectangle(new_tile_position, size, Colors::green);

    SnakeTile *new_tile = new SnakeTile(rectangle, this->tile_size, this->tile_height);
    new_tile->set_direction(new_tile_direction);
    this->insert_tile(new_tile);

    const std::vector<int> available_random_grid_pair = this->get_random_available_grid();

    glm::vec2 apple_coordinates = this->get_coordinates(available_random_grid_pair[0], available_random_grid_pair[1]);

    this->apple->set_x_position(apple_coordinates.x);
    this->apple->set_y_position(apple_coordinates.y);
}

std::vector<int> Snake::get_random_available_grid()
{
    int available_grids_size = this->available_grids.size();

    if (available_grids_size <= 0)
    {
        return {0, 0};
    }

    int index = Utils::get_random_integer(0, available_grids_size - 1);

    return this->available_grids[index];
}

void Snake::remove_available_grid_coordinate_pair(int x, int y)
{
    int available_grids_size = this->available_grids.size();

    for (int i = 0; i < available_grids_size; i++)
    {
        int current_x = this->available_grids[i][0];
        int current_y = this->available_grids[i][1];

        if (current_x == x && current_y == y)
        {
            this->available_grids.erase(this->available_grids.begin() + i);
            return;
        }
    }
}

void Snake::add_available_grid_coordinate_pair(int x, int y)
{
    this->available_grids.push_back({x, y});
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

bool Snake::check_apple_collision(SnakeTile *snake_head)
{
    if (this->apple->get_x_grid_axis() == snake_head->get_x_grid_axis() && this->apple->get_y_grid_axis() == snake_head->get_y_grid_axis())
        return true;

    return false;
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
    this->remove_available_grid_coordinate_pair(new_tile->get_x_grid_axis(), new_tile->get_y_grid_axis());

    if (this->head_tile != nullptr)
    {
        this->head_tile->previous = new_tile;
    }

    new_tile->next = this->head_tile;
    this->head_tile = new_tile;
}

void Snake::reset()
{
    this->delete_snake();
    this->create_initial_snake();

    const std::vector<int> available_random_grid_pair = this->get_random_available_grid();

    glm::vec2 apple_coordinates = this->get_coordinates(available_random_grid_pair[0], available_random_grid_pair[1]);
    glm::vec2 apple_size(this->tile_size, this->tile_height);

    Rectangle *apple_rectangle = new Rectangle(apple_coordinates, apple_size, Colors::red);
    this->apple = new SnakeTile(apple_rectangle, this->tile_size, this->tile_height);
    this->apple->set_has_borders(false);

    this->is_playing = true;
    this->is_game_over = false;
    this->current_direction = SNAKE_DIRECTION_LEFT;

    while (!this->inputs_queue.empty())
    {
        this->inputs_queue.pop();
    }
    this->inputs_queue.push(GLFW_KEY_LEFT);
}

void Snake::draw(GLuint shaderProgram, GLuint VAO)
{
    SnakeTile *current = this->head_tile;
    SnakeTile *last_tile = current; // The last tile is actually the "head" of the snake
    SnakeTile *snake_tail_tile = this->head_tile;

    if (this->is_playing)
    {
        this->current_tile_position += speed;
    }

    // add the grid pair to the available_grids
    if (this->current_tile_position >= this->tile_size)
    {
        this->add_available_grid_coordinate_pair(snake_tail_tile->get_x_grid_axis(), snake_tail_tile->get_y_grid_axis());
    }

    while (current != nullptr)
    {
        if (this->current_tile_position >= this->tile_size && current->next != nullptr)
        {
            current->set_x_position(current->next->get_x_position());
            current->set_y_position(current->next->get_y_position());
            current->set_direction(current->next->get_direction());
        }

        current->draw(shaderProgram, VAO);

        last_tile = current;
        current = current->next;
    }

    if (this->current_tile_position >= this->tile_size && last_tile != nullptr)
    {
        this->current_tile_position = 0.0f;

        if (!this->inputs_queue.empty())
        {
            int current_input = this->inputs_queue.front();

            while (!this->inputs_queue.empty())
            {
                if (this->inputs_queue.front() != current_input)
                    break;

                this->inputs_queue.pop();
            }

            switch (current_input)
            {
            case GLFW_KEY_LEFT:
                this->current_direction = SNAKE_DIRECTION_LEFT;
                break;
            case GLFW_KEY_RIGHT:
                this->current_direction = SNAKE_DIRECTION_RIGHT;
                break;
            case GLFW_KEY_UP:
                this->current_direction = SNAKE_DIRECTION_UP;
                break;
            case GLFW_KEY_DOWN:
                this->current_direction = SNAKE_DIRECTION_DOWN;
                break;
            default:
                break;
            }
        }

        switch (this->current_direction)
        {
        case SNAKE_DIRECTION_LEFT:
            last_tile->set_direction(SNAKE_DIRECTION_LEFT);
            last_tile->translate_x(-1 * this->tile_size);
            break;
        case SNAKE_DIRECTION_RIGHT:
            last_tile->set_direction(SNAKE_DIRECTION_RIGHT);
            last_tile->translate_x(this->tile_size);
            break;
        case SNAKE_DIRECTION_UP:
            last_tile->set_direction(SNAKE_DIRECTION_UP);
            last_tile->translate_y(this->tile_size);
            break;
        case SNAKE_DIRECTION_DOWN:
            last_tile->set_direction(SNAKE_DIRECTION_DOWN);
            last_tile->translate_y(-1 * this->tile_size);
            break;
        default:
            break;
        }

        this->remove_available_grid_coordinate_pair(last_tile->get_x_grid_axis(), last_tile->get_y_grid_axis());

        if (this->check_snake_collision(last_tile))
        {
            this->is_playing = false;
            this->is_game_over = true;
        }

        if (this->check_border_collision(last_tile))
        {
            // GAME OVER!!!
            this->is_playing = false;
            this->is_game_over = true;
        }

        if (this->check_apple_collision(last_tile))
        {
            this->set_new_apple();
        }

        current = this->head_tile;

        while (current != nullptr)
        {
            current->set_new_borders();

            current = current->next;
        }
    }

    this->draw_apple(shaderProgram, VAO);
}

void Snake::on_direction_change(int direction)
{
    if (this->head_tile == nullptr)
        return;

    this->inputs_queue.push(direction);
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

        if (i == 0)
        {
            current_tile->create_eyes();
        }
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

Snake::Snake(GLFWwindow *window, float tile_size) : window(window), is_playing(false), is_game_over(false), speed(0.02f), current_tile_position(0.0f), current_direction(SNAKE_DIRECTION_LEFT), initial_tile_count(3), tile_size(tile_size), head_tile(nullptr), apple(nullptr), available_grids(Dimensions::get_grid_coordinate_pairs())
{
    this->inputs_queue.push(GLFW_KEY_LEFT);
    this->create_initial_snake();

    const std::vector<int> available_random_grid_pair = this->get_random_available_grid();

    glm::vec2 apple_coordinates = this->get_coordinates(available_random_grid_pair[0], available_random_grid_pair[1]);
    glm::vec2 apple_size(this->tile_size, this->tile_height);

    Rectangle *apple_rectangle = new Rectangle(apple_coordinates, apple_size, Colors::red);
    this->apple = new SnakeTile(apple_rectangle, this->tile_size, this->tile_height);
    this->apple->set_has_borders(false);
}

Snake::~Snake()
{
    this->delete_snake();
}