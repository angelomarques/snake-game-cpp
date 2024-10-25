#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <glm/glm.hpp>
#include <vector>

class Colors
{
public:
    Colors();

    static glm::vec3 light_gray;
    static glm::vec3 medium_gray;
    static glm::vec3 dark_gray;
    static glm::vec3 green;
    static glm::vec3 red;
    static glm::vec3 black;
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

    static int screen_width;
    static int screen_height;

    static std::vector<std::vector<int>> get_grid_coordinate_pairs();
};

#endif // CONSTANTS_HPP
