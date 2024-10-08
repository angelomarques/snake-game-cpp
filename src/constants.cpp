#include "constants.hpp"

Colors::Colors() {}

glm::vec3 Colors::light_gray = glm::vec3(0.8f, 0.8f, 0.8f);
glm::vec3 Colors::medium_gray = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 Colors::dark_gray = glm::vec3(0.3f, 0.3f, 0.3f);
glm::vec3 Colors::green = glm::vec3(0.3f, 1.0f, 0.3f);
glm::vec3 Colors::red = glm::vec3(0.9f, 0.2f, 0.2f);

Dimensions::Dimensions() {}

int Dimensions::grid_axis_count = 20;
float Dimensions::total_width = 2.0f;
float Dimensions::total_height = 2.0f;

float Dimensions::positive_border_coordinate = 1.0f;
float Dimensions::negative_border_coordinate = -1.0f;