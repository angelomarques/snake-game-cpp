#include "layout.hpp"

GridLayout::GridLayout(int horizontal, int vertical) : horizontal(horizontal), vertical(vertical) {}

void GridLayout::draw(GLuint shaderProgram, GLuint VAO)
{
    glm::vec2 position(0.0f, 0.0f);
    glm::vec2 size(0.2f, 0.2f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}