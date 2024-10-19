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

protected:
    glm::vec3 color;

public:
    // Constructor
    Shape(const std::string &name, const glm::vec3 &color);

    virtual void draw(GLuint shaderProgram, GLuint VAO) const = 0;

    virtual ~Shape() = default;
};

class Rectangle : public Shape
{
    glm::vec2 size;

public:
    glm::vec2 position;

    Rectangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec3 &color);

    void draw(GLuint shaderProgram, GLuint VAO) const override;

    void translate_x(float distance);
    void translate_y(float distance);

    void set_width(float new_width);
    void set_height(float new_height);
};

#endif // SHAPE_HPP
