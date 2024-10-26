#include "constants.hpp"

Colors::Colors() {}

glm::vec4 Colors::light_gray = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
glm::vec4 Colors::medium_gray = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
glm::vec4 Colors::dark_gray = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
glm::vec4 Colors::green = glm::vec4(0.3f, 1.0f, 0.3f, 1.0f);
glm::vec4 Colors::red = glm::vec4(0.9f, 0.2f, 0.2f, 1.0f);
glm::vec4 Colors::black = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
glm::vec4 Colors::black_transparent = glm::vec4(0.1f, 0.1f, 0.1f, 0.9f);
glm::vec4 Colors::white = glm::vec4(0.9f, 0.8f, 0.8f, 1.0f);

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