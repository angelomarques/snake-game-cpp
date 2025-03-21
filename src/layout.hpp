#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GridLayout
{
    int horizontal, vertical;
    float line_width;

    glm::vec4 line_color;

public:
    GridLayout(int horizontal, int vertical);

    void draw(GLuint shaderProgram, GLuint VAO);
};

#endif // LAYOUT_HPP
