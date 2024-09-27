#include <GLFW/glfw3.h>
#include "shape.hpp"
#include <iostream>

// Constructor implementation
Shape::Shape(const std::string &name) : name(name) {}

Square::Square() : Shape("square") {}

void Square::draw() const
{
    // Draw a square using OpenGL's immediate mode (deprecated)
    glBegin(GL_QUADS);           // Start drawing a quadrilateral
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex2f(-0.5f, -0.5f);    // Bottom left
    glVertex2f(0.5f, -0.5f);     // Bottom right
    glVertex2f(0.5f, 0.5f);      // Top right
    glVertex2f(-0.5f, 0.5f);     // Top left
    glEnd();                     // End drawing the quadrilateral
}
