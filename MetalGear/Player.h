#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Gun.h"
#include <vector>
#include <map>

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

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

private:
	map<Item*, int> items;
	map<Item*, int>::iterator currentItemIt;
	int health;
	Gun* gun;
	bool equippedGun;
	int punchRate = 500;
	int lastPunch = 500;
	Scene* scene;
	glm::ivec2 tileMapDispl, posPlayer;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};

#endif // _PLAYER_INCLUDE