#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include <unordered_set>
#include "FireBall.h"
#include "BossAtack.h"
class TileMap;


class Enemy{
public:
	virtual ~Enemy() {}

	
	virtual void init(ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime, const glm::ivec2& playerPos) = 0;
	enum LookingDirection
	{
		DOWN, UP, LEFT, RIGHT
	};

	
	virtual void render();
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition() const { return posEnemy; }
	glm::ivec2 getSize() const { return size; }
	virtual bool checkCollisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const;
	virtual void takeDamage(int dmg);
	bool isDead() const { return health <= 0; }
	int getHealth() const { return health; }
	int getDamage() const { return damage; }
	virtual bool seePlayer(const glm::ivec2& playerPos) const;

protected:
	glm::vec2 posEnemy;
	glm::ivec2 tileMapDispl;
	glm::ivec2 size;
	vector<int> patrolSquare;
	vector<FireBall*> fireBalls;
	vector<BossAtack*> bossAtacks;
	bool dead = false;

	Player* player;
	int health;
	int damage;
	float speed;
	bool playerHasBeenDetected;

	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	ShaderProgram* s;
	int lookingDirection;
};
#endif 