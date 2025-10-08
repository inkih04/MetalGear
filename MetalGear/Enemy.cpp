#include "Enemy.h"

void Enemy::render()
{
	sprite->render();
}


void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

void Enemy::takeDamage(int dmg)
{
	health -= dmg;
	if (health < 0)
		health = 0;
}

bool Enemy::checkCollisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const
{
	return true;

}