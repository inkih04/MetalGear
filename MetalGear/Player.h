#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Item.h"
#include <vector>


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	int checkMap(glm::ivec2 &newPos);
	void checkEnemies(int deltaTime);
	void addItem(Item* item) { 
		if (items.empty()) currentItem = 0;
		if (item->getType() == ItemTypes::GUN)
			gun = item;
		items.push_back(item); 
	}
	
private:
	vector<Item*> items;
	int currentItem;

	Item* gun;
	bool equippedGun;

	glm::ivec2 tileMapDispl, posPlayer;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


