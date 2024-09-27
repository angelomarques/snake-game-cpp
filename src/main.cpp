#include <GLFW/glfw3.h>
#include <iostream>
#include "shape.hpp"

// Function to handle resizing of the window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height); // Adjusts the OpenGL viewport to match window size
}

int main()
{
    const int screen_width = 800;
    const int screen_height = 600;

    // Initialize GLFW library
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "OpenGL Square", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's OpenGL context current
    glfwMakeContextCurrent(window);

    // Set the callback function for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL viewport initial settings
    glViewport(0, 0, screen_width, screen_height);

    Square square_shape;

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen with a black color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        square_shape.draw();

        // Swap buffers (display the rendered frame)
        glfwSwapBuffers(window);

        // Poll events (keyboard, mouse, etc.)
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
