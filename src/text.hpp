#ifndef TEXT_HPP
#define TEXT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "constants.hpp"

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
    GLuint VAO, VBO;
    Shader shader;

    std::map<GLchar, Character> Characters;

    void initFreeType(const char *font_path);

public:
    Text();

    void render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color);

    void use();
};

#endif // TEXT_HPP