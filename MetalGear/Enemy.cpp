#include "Enemy.h"
#include "TileMap.h"
#include "AudioManager.h"

void Enemy::render()
{
	if (!dead) 
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
	if (health <= 0) {
		dead = true;
	}

}

bool Enemy::checkCollisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const
{
	if (dead) return false;

	bool collisionX = posEnemy.x < playerPos.x + playerSize.x &&
		posEnemy.x + size.x > playerPos.x;

	bool collisionY = posEnemy.y < playerPos.y + playerSize.y &&
		posEnemy.y + size.y > playerPos.y + 16;

	return collisionX && collisionY;
}

bool Enemy::seePlayer(const glm::ivec2& playerPos) const
{
	if (map == nullptr)
		return false;
	if (playerHasBeenDetected) return true;

	int tileSize = map->getTileSize();
	int enemyTileX = (posEnemy.x + size.x / 2) / tileSize;
	int enemyTileY = (posEnemy.y + size.y / 2) / tileSize;
	int playerTileX = (playerPos.x + 7) / tileSize;
	int playerTileY = (playerPos.y + 13) / tileSize;

	int dx = playerTileX - enemyTileX;
	int dy = playerTileY - enemyTileY;

	switch (lookingDirection)
	{
	case LEFT:
		if (dx >= 0 || dy != 0) return false;  
		break;
	case RIGHT:
		if (dx <= 0 || dy != 0) return false;  
		break;
	case UP:
		if (dy >= 0 || dx != 0) return false;  
		break;
	case DOWN:
		if (dy <= 0 || dx != 0) return false;  
		break;
	}

	float x0 = float(enemyTileX);
	float y0 = float(enemyTileY);
	float x1 = float(playerTileX);
	float y1 = float(playerTileY);

	float dxf = x1 - x0;
	float dyf = y1 - y0;

	std::unordered_set<int> blockingTiles = map->getBlockTileIds();
	glm::ivec2 mapSize = map->getMapSize();

	int N = std::max(abs(int(dxf)), abs(int(dyf)));

	if (N == 0)
		return true;

	for (int step = 0; step <= N; step++)
	{
		float t = float(step) / float(N);
		float x = x0 + t * dxf;
		float y = y0 + t * dyf;

		int tileX = int(x);
		int tileY = int(y);

		if (tileX < 0 || tileX >= mapSize.x || tileY < 0 || tileY >= mapSize.y)
			return false;

		int currentTile = map->getTileAt(tileX, tileY);

		if (step > 0 && step < N)
		{
			if (blockingTiles.count(currentTile))
				return false;
		}
	}

	return true;
}