#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Gun.h"
#include <map>
#include <iostream>

class Scene;
class Item;

class Player
{
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Scene* scene);
    void update(int deltaTime);
    void render();
    bool canPunch();
    void heal(int life);
    void setTileMap(TileMap* tileMap);
    void setPosition(const glm::vec2& pos);
    int checkMap(glm::ivec2& newPos);
    void openDor();

    glm::ivec2 getPosition() const { return posPlayer; }
    int getHealth() const { return health; }
    bool hasGun() const { return gun != nullptr; }
    bool isGunEquipped() const { return equippedGun; }
    int getAmmo() const { return gun != nullptr ? gun->getAmmo() : 0; }

    void checkEnemies(int deltaTime);
    void addItem(Item* item);
    void takeDamage(int dmg);
    void reloadGun(int ammoCount) {
        if (gun != nullptr) gun->reload(ammoCount);
    };

    Item* getCurrentItem() const {
        if (currentItemIt != items.end()) {
            return currentItemIt->first;
        }
        return nullptr;
    }

    int getItemCount(Item* item) const {
        auto it = items.find(item);
        if (it != items.end()) {
            return it->second;
        }
        return 0;
    }

private:
    float speed;
    bool godMode;
    std::map<Item*, int> items;
    std::map<Item*, int>::iterator currentItemIt;
    int health;
    Gun* gun;
    bool equippedGun;
    int punchRate = 500;
    int lastPunch = 500;
    Scene* scene;
    glm::ivec2 tileMapDispl;
    glm::vec2 posPlayer;
    Texture spritesheet;
    Sprite* sprite;
    TileMap* map;
};

#endif // _PLAYER_INCLUDE