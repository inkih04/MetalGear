#pragma once

#include "Sprite.h"


class Enemy{
public:
	virtual ~Enemy() {}

	// Métodos abstractos
	virtual void init(ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;

	//comunes
	void render();
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition() const { return posEnemy; }
	glm::ivec2 getSize() const { return size; }

	void takeDamage(int dmg);
	bool isDead() const { return health <= 0; }
	int getHealth() const { return health; }
	int getDamage() const { return damage; }
	bool seePlayer(const glm::ivec2& playerPos) const;

	bool checkCollisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const;

protected:
	glm::ivec2 posEnemy;
	glm::ivec2 tileMapDispl;
	glm::ivec2 size;
	int health;
	int damage;

	Texture spritesheet;
	Sprite* sprite;
};

