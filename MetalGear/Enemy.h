#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include <unordered_set>
class TileMap;


class Enemy{
public:
	virtual ~Enemy() {}

	// Métodos abstractos
	virtual void init(ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime, const glm::ivec2& playerPos) = 0;
	enum LookingDirection
	{
		DOWN, UP, LEFT, RIGHT
	};

	//comunes
	void render();
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition() const { return posEnemy; }
	glm::ivec2 getSize() const { return size; }
	bool checkCollisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const;
	void takeDamage(int dmg);
	bool isDead() const { return health <= 0; }
	int getHealth() const { return health; }
	int getDamage() const { return damage; }
	bool seePlayer(const glm::ivec2& playerPos) const;

protected:
	glm::ivec2 posEnemy;
	glm::ivec2 tileMapDispl;
	glm::ivec2 size;
	int health;
	int damage;
	int speed;
	bool playerHasBeenDetected;

	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int lookingDirection;
};
#endif 