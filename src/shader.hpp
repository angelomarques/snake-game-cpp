#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader
{
private:
    GLuint shader_program;

    std::string
    readShaderSource(const std::string &filePath);

    GLuint compileShader(GLenum type, const std::string &source);

    GLuint createShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);

public:
    Shader(std::string vertex_shader_source_path, std::string fragment_shader_source_path);

    GLuint get_shader_program();

    ~Shader();
};

#endif // SHADER_HPP
