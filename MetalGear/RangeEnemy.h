#pragma once

#include "Enemy.h"
#include "Guard.h"
#include "Player.h"

class RangeEnemy : public Enemy
{
public:
	RangeEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map, const vector<int>& patrolSquare, Guard guard, int direction,Player* player);
	void init(ShaderProgram& shaderProgram) override;
	bool canShoot();
	void update(int deltaTime, const glm::ivec2& playerPos) override;
	void move(const glm::ivec2& playerPos);
	void atack();
	void render() override;

private:
	bool tryMove(int dir);
	void patrol();
	void guard();

	Player* player;
	int lastShotTime;
	int fireRate;
	int health;
	int patrolState;
	int patrolProgress;
	Guard guardPosition;
	int direction;
	int currentGuardIndex;
	int guardTimer;

};