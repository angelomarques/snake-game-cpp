#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::string Shader::readShaderSource(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error: Shader compilation failed\n"
                  << infoLog << std::endl;
    }

    return shader;
}

GLuint Shader::createShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Error: Shader program linking failed\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint Shader::get_shader_program()
{
    return this->shader_program;
}

Shader::Shader(std::string vertex_shader_source_path, std::string fragment_shader_source_path)
{
    std::string vertexShaderSource = this->readShaderSource("src/shaders/vertex_shader.glsl");
    std::string fragmentShaderSource = this->readShaderSource("src/shaders/fragment_shader.glsl");
    this->shader_program = this->createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader()
{
    std::cout << "Deleting shader program..." << std::endl;
    glDeleteProgram(this->shader_program);
}
