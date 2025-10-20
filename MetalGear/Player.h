#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Gun.h"
#include <vector>


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Item;

class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	bool canPunch();
	void heal(int life);
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	int checkMap(glm::ivec2 &newPos);
	glm::ivec2 getPosition() const { return posPlayer; }
	void checkEnemies(int deltaTime);
	void addItem(Item* item) { 
		if (items.empty()) currentItem = 0;
		if (item->getType() == ItemTypes::GUN)
			gun = static_cast<Gun*>(item);
		items.push_back(item); 
	}
	void takeDamage(int dmg);
	
private:
	vector<Item*> items;
	int currentItem;
	int health;
	Gun* gun;
	bool equippedGun;
	int punchRate = 500;
	int lastPunch = 500;

	glm::ivec2 tileMapDispl, posPlayer;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


