#include "snake_tile.hpp"
#include "shape.hpp"
#include "constants.hpp"
#include "utils.hpp"

SnakeTile::SnakeTile(Rectangle *rectangle, float tile_size, float tile_height) : tile_size(tile_size), tile_height(tile_height), rectangle(rectangle), direction(SNAKE_DIRECTION_LEFT), border_reference({true, false, true, false}), next(nullptr), previous(nullptr)
{
    std::vector<int> grid_reference = this->get_grid_reference(this->rectangle->position);

    this->x_grid_axis = grid_reference[0];
    this->y_grid_axis = grid_reference[1];

    this->set_borders();
};

SnakeTile::~SnakeTile()
{
    if (this->rectangle != nullptr)
    {
        std::cout << "Deleting snake tile rectangle..." << std::endl;
        delete this->rectangle;
    }
}

void SnakeTile::set_eyes_position()
{
    if (this->eyes.size() == 2)
    {
        switch (this->direction)
        {
        case SNAKE_DIRECTION_LEFT:
            this->eyes[0].position.x = this->get_x_position() - 0.25 * this->tile_size;
            this->eyes[0].position.y = this->get_y_position();
            this->eyes[0].set_width(eye_height);
            this->eyes[0].set_height(eye_width);

            this->eyes[1].position.x = this->get_x_position() - 0.25 * this->tile_size;
            this->eyes[1].position.y = this->get_y_position() - 0.5 * this->tile_height;
            this->eyes[1].set_width(eye_height);
            this->eyes[1].set_height(eye_width);
            break;
        case SNAKE_DIRECTION_RIGHT:
            this->eyes[0].position.x = this->get_x_position() + 0.25 * this->tile_size;
            this->eyes[0].position.y = this->get_y_position() - 0.5 * this->tile_height;
            this->eyes[0].set_width(eye_height);
            this->eyes[0].set_height(eye_width);

            this->eyes[1].position.x = this->get_x_position() + 0.25 * this->tile_size;
            this->eyes[1].position.y = this->get_y_position();
            this->eyes[1].set_width(eye_height);
            this->eyes[1].set_height(eye_width);
            break;

        case SNAKE_DIRECTION_UP:
            this->eyes[0].position.x = this->get_x_position() + 0.25 * this->tile_size;
            this->eyes[0].position.y = this->get_y_position() + 0.25 * this->tile_height;

            this->eyes[1].position.x = this->get_x_position() - 0.25 * this->tile_size;
            this->eyes[1].position.y = this->get_y_position() + 0.25 * this->tile_height;
            break;

        case SNAKE_DIRECTION_DOWN:
            this->eyes[0].position.x = this->get_x_position() - 0.25 * this->tile_size;
            this->eyes[0].position.y = this->get_y_position() - 0.5 * this->tile_height;

            this->eyes[1].position.x = this->get_x_position() + 0.25 * this->tile_size;
            this->eyes[1].position.y = this->get_y_position() - 0.5 * this->tile_height;
            break;

        default:
            break;
        }
    }
}

void SnakeTile::create_eyes()
{
    this->eyes.clear();

    glm::vec2 position(this->get_x_position(), this->get_y_position());
    glm::vec2 size(this->eye_width, this->eye_height);

    Rectangle right_eye(position, size, Colors::black);
    Rectangle left_eye(position, size, Colors::black);

    this->eyes.push_back(right_eye);
    this->eyes.push_back(left_eye);

    this->set_eyes_position();
}

void SnakeTile::set_has_borders(bool value)
{
    this->has_borders = value;
}

void SnakeTile::set_new_borders()
{
    int current_x_grid = this->get_x_grid_axis();
    int current_y_grid = this->get_y_grid_axis();

    this->border_reference = {true, true, true, true};

    if (this->previous != nullptr)
    {
        bool has_sibling_right = this->previous->get_y_grid_axis() == current_y_grid && this->previous->get_x_grid_axis() > current_x_grid;
        bool has_sibling_left = this->previous->get_y_grid_axis() == current_y_grid && this->previous->get_x_grid_axis() < current_x_grid;
        bool has_sibling_top = this->previous->get_x_grid_axis() == current_x_grid && this->previous->get_y_grid_axis() > current_y_grid;
        bool has_sibling_bottom = this->previous->get_x_grid_axis() == current_x_grid && this->previous->get_y_grid_axis() < current_y_grid;

        if (has_sibling_right)
        {
            this->border_reference[1] = false;
        }

        if (has_sibling_left)
        {
            this->border_reference[3] = false;
        }

        if (has_sibling_top)
        {
            this->border_reference[0] = false;
        }

        if (has_sibling_bottom)
        {
            this->border_reference[2] = false;
        }
    }

    if (this->next != nullptr)
    {
        bool has_sibling_right = this->next->get_y_grid_axis() == current_y_grid && this->next->get_x_grid_axis() > current_x_grid;
        bool has_sibling_left = this->next->get_y_grid_axis() == current_y_grid && this->next->get_x_grid_axis() < current_x_grid;
        bool has_sibling_top = this->next->get_x_grid_axis() == current_x_grid && this->next->get_y_grid_axis() > current_y_grid;
        bool has_sibling_bottom = this->next->get_x_grid_axis() == current_x_grid && this->next->get_y_grid_axis() < current_y_grid;

        if (has_sibling_right)
        {
            this->border_reference[1] = false;
        }

        if (has_sibling_left)
        {
            this->border_reference[3] = false;
        }

        if (has_sibling_top)
        {
            this->border_reference[0] = false;
        }

        if (has_sibling_bottom)
        {
            this->border_reference[2] = false;
        }
    }

    this->set_borders();
}

Rectangle SnakeTile::get_new_border(int location)
{
    glm::vec2 position(this->get_x_position(), this->get_y_position());
    glm::vec2 size(this->border_width, this->tile_height);

    switch (location)
    {
    case SNAKE_DIRECTION_LEFT:
        position.x = position.x - (this->tile_size / 2) + (this->border_width / 2);
        break;
    case SNAKE_DIRECTION_RIGHT:
        position.x = position.x + (this->tile_size / 2) - (this->border_width / 2);
        break;
    case SNAKE_DIRECTION_UP:
        size.x = tile_size;
        size.y = border_width;
        position.y = position.y + (this->tile_height / 2) - (this->border_width / 2);
        break;
    case SNAKE_DIRECTION_DOWN:
        size.x = tile_size;
        size.y = border_width;
        position.y = position.y - (this->tile_height) + (this->border_width / 2);
        break;
    default:
        break;
    }

    Rectangle border(position, size, Colors::black);

    return border;
}

void SnakeTile::set_borders()
{
    this->borders.clear();

    const int border_reference_size = this->border_reference.size();
    for (int i = 0; i < border_reference_size; i++)
    {
        switch (i)
        {
        case 0:
        {
            if (this->border_reference[i])
            {
                Rectangle top_border = this->get_new_border(SNAKE_DIRECTION_UP);
                this->borders.push_back(top_border);
            }
            break;
        }
        case 1:
        {
            if (this->border_reference[i])
            {
                Rectangle right_border = this->get_new_border(SNAKE_DIRECTION_RIGHT);
                this->borders.push_back(right_border);
            }
            break;
        }
        case 2:
        {
            if (this->border_reference[i])
            {
                Rectangle bottom_border = this->get_new_border(SNAKE_DIRECTION_DOWN);
                this->borders.push_back(bottom_border);
            }
            break;
        }
        case 3:
        {
            if (this->border_reference[i])
            {
                Rectangle left_border = this->get_new_border(SNAKE_DIRECTION_LEFT);
                this->borders.push_back(left_border);
            }
            break;
        }
        default:
            break;
        }
    }
}

void SnakeTile::set_direction(int new_direction)
{
    this->direction = new_direction;
}

int SnakeTile::get_direction()
{
    return this->direction;
}

void SnakeTile::translate_x(float distance)
{
    this->rectangle->translate_x(distance);

    this->x_grid_axis = this->get_single_grid_reference(this->rectangle->position.x, this->tile_size);

    this->set_eyes_position();
}

void SnakeTile::translate_y(float distance)
{
    this->rectangle->translate_y(distance);

    this->y_grid_axis = this->get_single_grid_reference(this->rectangle->position.y, this->tile_height);

    this->set_eyes_position();
}

float SnakeTile::get_x_position()
{
    return this->rectangle->position.x;
}
void SnakeTile::set_x_position(float new_position)
{
    this->rectangle->position.x = new_position;

    this->x_grid_axis = this->get_single_grid_reference(this->rectangle->position.x, this->tile_size);

    this->set_eyes_position();
}

float SnakeTile::get_y_position()
{
    return this->rectangle->position.y;
}
void SnakeTile::set_y_position(float new_position)
{
    this->rectangle->position.y = new_position;

    this->y_grid_axis = this->get_single_grid_reference(this->rectangle->position.y, this->tile_height);

    this->set_eyes_position();
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

    if (this->has_borders)
    {
        for (Rectangle border : this->borders)
        {
            border.draw(shaderProgram, VAO);
        }
    }

    if (this->eyes.size() > 0)
    {
        for (Rectangle eye : this->eyes)
        {
            eye.draw(shaderProgram, VAO);
        }
    }
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