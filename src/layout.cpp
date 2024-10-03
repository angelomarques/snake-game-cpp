#include "layout.hpp"
#include "shape.hpp"

GridLayout::GridLayout(int horizontal, int vertical) : horizontal(horizontal), vertical(vertical) {}

void GridLayout::draw(GLuint shaderProgram, GLuint VAO)
{
    glm::vec2 left_rectangle_position(-1.0f, 0.0f);
    glm::vec2 left_rectangle_size(0.01f, 2.0f);
    Rectangle left_rectangle(left_rectangle_position, left_rectangle_size);
    left_rectangle.draw(shaderProgram, VAO);

    glm::vec2 right_rectangle_position(1.0f, 0.0f);
    glm::vec2 right_rectangle_size(0.01f, 2.0f);
    Rectangle right_rectangle(right_rectangle_position, right_rectangle_size);
    right_rectangle.draw(shaderProgram, VAO);

    glm::vec2 top_rectangle_position(0.0f, 1.0f);
    glm::vec2 top_rectangle_size(2.0f, 0.01f);
    Rectangle top_rectangle(top_rectangle_position, top_rectangle_size);
    top_rectangle.draw(shaderProgram, VAO);

    glm::vec2 bottom_rectangle_position(0.0f, -1.0f);
    glm::vec2 bottom_rectangle_size(2.0f, 0.01f);
    Rectangle bottom_rectangle(bottom_rectangle_position, bottom_rectangle_size);
    bottom_rectangle.draw(shaderProgram, VAO);
}