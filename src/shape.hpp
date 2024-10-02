#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shape
{
private:
    std::string name;

public:
    // Constructor
    Shape(const std::string &name);

    virtual void draw(GLuint shaderProgram, GLuint VAO) const = 0;

    virtual ~Shape() = default;
};

class Rectangle : public Shape
{
    glm::vec2 position;
    glm::vec2 size;

public:
    Rectangle(const glm::vec2 &position, const glm::vec2 &size);

    void draw(GLuint shaderProgram, GLuint VAO) const override;

    void translate_x(float distance);
    void translate_y(float distance);
};

#endif // SHAPE_HPP
