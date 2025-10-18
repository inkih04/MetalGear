#pragma once

#include "Enemy.h"
#include "Guard.h"

class RangeEnemy : public Enemy
{
public:
	RangeEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map, const vector<int>& patrolSquare, Guard guard, int direction);
	void init(ShaderProgram& shaderProgram) override;
	void update(int deltaTime, const glm::ivec2& playerPos) override;
	void move(const glm::ivec2& playerPos);

private:
	bool tryMove(int dir);
	void patrol();
	void guard();

	int health;
	int patrolState;
	int patrolProgress;
	Guard guardPosition;
	int direction;
	int currentGuardIndex;
	int guardTimer;

};