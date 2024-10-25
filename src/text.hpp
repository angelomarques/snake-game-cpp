#ifndef TEXT_HPP
#define TEXT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>

struct Character
{
    GLuint textureID;   // ID handle of the glyph texture
    glm::ivec2 size;    // Size of the glyph
    glm::ivec2 bearing; // Offset from baseline to left/top of glyph
    GLuint advance;     // Horizontal offset to advance to next glyph
};

class Text
{
private:
    GLuint shader_program;
    GLuint VAO, VBO;

    std::map<GLchar, Character> Characters;

public:
    Text(GLuint shader_program, std::map<GLchar, Character> Characters);

    void render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

#endif // TEXT_HPP