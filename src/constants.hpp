#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

class Colors
{
public:
    Colors();

    static glm::vec3 light_gray;
    static glm::vec3 medium_gray;
    static glm::vec3 dark_gray;
    static glm::vec3 green;
    static glm::vec3 red;
};

class Dimensions
{
public:
    Dimensions();

    static int grid_axis_count;
    static float total_width;
    static float total_height;

    static float positive_border_coordinate;
    static float negative_border_coordinate;
};

#endif // CONSTANTS_HPP
