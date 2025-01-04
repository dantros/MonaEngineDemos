#pragma once

#include <vector>

struct HighLevelGame
{
    unsigned int currentLevel = 0;
    unsigned int coinsCollected = 0;
    float currentTime = 0.f;
    unsigned int points = 0;

    struct Level
    {
        unsigned int coins;
        unsigned int monsters; // pending implementation
    };

    const std::vector<Level> levels
    {
        {10, 1},
        {5, 2},
        {10, 3},
        {20, 4},
        {30, 4},
        {5, 8},
        {3, 10},
        {50, 1}
    };
};