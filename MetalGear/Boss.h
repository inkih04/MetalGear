#pragma once

#include "Enemy.h"
#include "Player.h"

class Boss : public Enemy
{
public:
	Boss(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map, int direction, Player* player);
	void init(ShaderProgram& shaderProgram) override;
	bool canShoot();
	void update(int deltaTime, const glm::ivec2& playerPos) override;
	bool checkCollisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const override;
	void move(const glm::ivec2& playerPos);
	void atack();
	void render() override;
	void takeDamage(int dmg) override;
	bool seePlayer(const glm::ivec2& playerPos) const override;

private:
	void teleport();

	int lastShotTime;
	int fireRate;
	int direction;

	int teleportTimer;
	int teleportInterval;
	int currentPositionIndex;
	std::vector<glm::ivec2> teleportPositions;

	int damageCounter;
	int damageThreshold;
	int lastHealthCheck;
};