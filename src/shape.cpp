#include "shape.hpp"
#include <iostream>

// Constructor implementation
Shape::Shape(const std::string &name, const glm::vec4 &color) : name(name), color(color) {}

void Rectangle::set_width(float new_width)
{
    this->size.x = new_width;
}

void Rectangle::set_height(float new_height)
{
    this->size.y = new_height;
}

void Rectangle::draw(GLuint shaderProgram, GLuint VAO) const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->position, 0.0f));
    model = glm::scale(model, glm::vec3(this->size, 1.0f));

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Render the rectangle with a custom color
    glUniform4fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(this->color));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Rectangle::translate_x(float distance)
{
    this->position.x += distance;
}

void Rectangle::translate_y(float distance)
{
    this->position.y += distance;
}

Rectangle::Rectangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) : Shape("rectangle", color), size(size), position(position)
{
}