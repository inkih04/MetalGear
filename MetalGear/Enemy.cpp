#include "Enemy.h"
#include "TileMap.h"

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

bool Enemy::seePlayer(const glm::ivec2& playerPos) const
{
	if (map == nullptr)
		return false;

	int tileSize = map->getTileSize();

	int enemyTileX = (posEnemy.x + size.x / 2) / tileSize;
	int enemyTileY = (posEnemy.y + size.y / 2) / tileSize;
	int playerTileX = (playerPos.x + 7) / tileSize;
	int playerTileY = (playerPos.y + 13) / tileSize;

	int dx = playerTileX - enemyTileX;
	int dy = playerTileY - enemyTileY;

	int distance = 0;  
	int perpendicular = 0;  

	switch (lookingDirection)
	{
	case LEFT:
		if (dx > 0) return false;  
		distance = -dx;
		perpendicular = abs(dy);
		break;
	case RIGHT:
		if (dx < 0) return false;  
		distance = dx;
		perpendicular = abs(dy);
		break;
	case UP:
		if (dy > 0) return false;  
		distance = -dy;
		perpendicular = abs(dx);
		break;
	case DOWN:
		if (dy < 0) return false;  
		distance = dy;
		perpendicular = abs(dx);
		break;
	}

	int maxWidth;
	if (distance == 0)
		maxWidth = 1; 
	else if (distance <= 3)
		maxWidth = distance;  
	else
		maxWidth = 3; 

	if (perpendicular > maxWidth)
		return false;

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