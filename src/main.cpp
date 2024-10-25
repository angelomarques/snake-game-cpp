#include "shader.hpp"
#include "game.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "text.hpp"

// Function to handle resizing of the window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height); // Adjusts the OpenGL viewport to match window size
}

int main()
{
    const GLint SCREEN_WIDTH = 1000;
    const GLint SCREEN_HEIGHT = 1000;

    // Initialize GLFW library
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Set GLFW properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Square", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's OpenGL context current
    glfwMakeContextCurrent(window);

    // Set the callback function for window resizing
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // OpenGL viewport initial settings
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    Game game(window);

    // Create shader program
    Shader text_shader("src/shaders/text_vertex_shader.glsl", "src/shaders/text_fragment_shader.glsl");

    Text my_text(text_shader.get_shader_program());

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.render();

        text_shader.use();

        // Setup projection matrix
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), 0.0f, static_cast<float>(SCREEN_HEIGHT));
        glUniformMatrix4fv(glGetUniformLocation(text_shader.get_shader_program(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Render text
        my_text.render("This is from the class", 25.0f, 500.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

        // Swap buffers (display the rendered frame)
        glfwSwapBuffers(window);

        // Poll events (keyboard, mouse, etc.)
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
