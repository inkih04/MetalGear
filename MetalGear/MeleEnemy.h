#ifndef _BASIC_ENEMY_INCLUDE
#define _BASIC_ENEMY_INCLUDE

#include "Enemy.h"
#include "Guard.h"

class MeleEnemy : public Enemy
{
public:
	MeleEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map, const vector<int>& patrolSquare, Guard guard, int direction, Player* player);
	void init(ShaderProgram& shaderProgram) override;
	void update(int deltaTime, const glm::ivec2& playerPos) override;
	void move(const glm::ivec2& playerPos);

private:
	bool tryMove(int dir);
	void retreat();
	void patrol();
	void guard();

	int health;
	static const int RETREAT_COOLDOWN_TIME = 1000;
	int retreatCooldown;
	bool isRetreating;
	int patrolState;  
	int patrolProgress;  
	Guard guardPosition;
	int direction;
	int currentGuardIndex;    
	int guardTimer;            
	
};

#endif 