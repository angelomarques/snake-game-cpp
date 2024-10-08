#include "utils.hpp"

Utils::Utils() {}

int Utils::get_random_integer(int min, int max)
{
    // Seed with a real random value, if available
    std::random_device rd;

    // Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(rd());

    // Define the range: 1 to 20 inclusive
    std::uniform_int_distribution<> distrib(min, max);

    // Generate a random number
    int res = distrib(gen);

    return res;
}