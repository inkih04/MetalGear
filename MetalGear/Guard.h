#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Guard {
    int time;
    std::vector<int> guardPosition;

    Guard()
        : guardPosition(), time(0) {
    }

    Guard(std::vector<int> position, int transitionTime)
        : guardPosition(std::move(position)), time(transitionTime){
    }
};