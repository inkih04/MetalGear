#ifndef _BASIC_ENEMY_INCLUDE
#define _BASIC_ENEMY_INCLUDE

#include "Enemy.h"

class BasicEnemy : public Enemy
{
public:
	BasicEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram);;
	void init(ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;

private:
	int health;
	
};

#endif 