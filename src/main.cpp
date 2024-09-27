#include <GLFW/glfw3.h>
#include <iostream>

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

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen with a black color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a square using OpenGL's immediate mode (deprecated)
        glBegin(GL_QUADS);           // Start drawing a quadrilateral
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        glVertex2f(-0.5f, -0.5f);    // Bottom left
        glVertex2f(0.5f, -0.5f);     // Bottom right
        glVertex2f(0.5f, 0.5f);      // Top right
        glVertex2f(-0.5f, 0.5f);     // Top left
        glEnd();                     // End drawing the quadrilateral

        // Swap buffers (display the rendered frame)
        glfwSwapBuffers(window);

        // Poll events (keyboard, mouse, etc.)
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
