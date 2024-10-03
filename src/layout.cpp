#include "layout.hpp"
#include "shape.hpp"
#include "colors.hpp"

GridLayout::GridLayout(int horizontal, int vertical) : horizontal(horizontal), vertical(vertical)
{
    this->line_width = 0.002f;

    this->line_color = Colors::dark_gray;
}

void GridLayout::draw(GLuint shaderProgram, GLuint VAO)
{
    int horizontal_lines_count = this->vertical + 1;
    float horizontal_lines_threshold = 2.0f / this->vertical;

    for (int i = 0; i < horizontal_lines_count; i++)
    {
        float y_position = 1.0f - (horizontal_lines_threshold * i);

        glm::vec2 horizontal_line_position(0.0f, y_position);
        glm::vec2 horizontal_line_size(2.0f, this->line_width);
        Rectangle horizontal_line(horizontal_line_position, horizontal_line_size, this->line_color);
        horizontal_line.draw(shaderProgram, VAO);
    }

    int vertical_lines_count = this->horizontal + 1;
    float vertical_lines_threshold = 2.0f / this->horizontal;

    for (int i = 0; i < vertical_lines_count; i++)
    {
        float x_position = 1.0f - (vertical_lines_threshold * i);

        glm::vec2 vertical_line_position(x_position, 0.0f);
        glm::vec2 vertical_line_size(this->line_width, 2.0f);
        Rectangle vertical_line(vertical_line_position, vertical_line_size, this->line_color);
        vertical_line.draw(shaderProgram, VAO);
    }
}