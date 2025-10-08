#pragma once
#include <glm/glm.hpp>
#include <vector>

struct ChangeMap {
    vector<int> idTiles;
    int idMap;
    glm::ivec2 newPosition;

    ChangeMap()
        : idTiles(), idMap(0), newPosition(0, 0) {
    }

    ChangeMap(std::vector<int> tiles, int newMap, glm::ivec2 pos)
        : idTiles(std::move(tiles)), idMap(newMap), newPosition(pos) {
    }
};

