#include "constants.hpp"

Colors::Colors() {}

glm::vec3 Colors::light_gray = glm::vec3(0.8f, 0.8f, 0.8f);
glm::vec3 Colors::medium_gray = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 Colors::dark_gray = glm::vec3(0.3f, 0.3f, 0.3f);
glm::vec3 Colors::green = glm::vec3(0.3f, 1.0f, 0.3f);
glm::vec3 Colors::red = glm::vec3(0.9f, 0.2f, 0.2f);
glm::vec3 Colors::black = glm::vec3(0.1f, 0.1f, 0.1f);

Dimensions::Dimensions() {}

int Dimensions::grid_axis_count = 10;
float Dimensions::total_width = 2.0f;
float Dimensions::total_height = 2.0f;

float Dimensions::positive_border_coordinate = 1.0f;
float Dimensions::negative_border_coordinate = -1.0f;

int Dimensions::screen_width = 1000;
int Dimensions::screen_height = 1000;

std::vector<std::vector<int>> Dimensions::get_grid_coordinate_pairs()
{
    std::vector<std::vector<int>> res;

    for (int x = 1; x <= grid_axis_count; x++)
    {
        for (int y = 1; y <= grid_axis_count; y++)
        {
            res.push_back({x, y});
        }
    }

    return res;
}