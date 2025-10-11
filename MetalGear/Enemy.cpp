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

	// Calcular el centro del enemigo y del jugador en tiles
	float x0 = float(posEnemy.x + size.x / 2) / tileSize;
	float y0 = float(posEnemy.y + size.y / 2) / tileSize;
	float x1 = float(playerPos.x + 7) / tileSize;
	float y1 = float(playerPos.y + 13) / tileSize;

	float dx = x1 - x0;
	float dy = y1 - y0;

	// VERIFICAR DIRECCIÓN: El jugador debe estar en la dirección correcta
	switch (lookingDirection)
	{
	case LEFT:
		if (dx >= 0) return false;  // El jugador está a la derecha o en la misma X
		break;
	case RIGHT:
		if (dx <= 0) return false;  // El jugador está a la izquierda o en la misma X
		break;
	case UP:
		if (dy >= 0) return false;  // El jugador está abajo o en la misma Y
		break;
	case DOWN:
		if (dy <= 0) return false;  // El jugador está arriba o en la misma Y
		break;
	}

	// IDs de tiles bloqueantes
	std::vector<int> blockingTiles = {
		3,4,5,6,7,9,10,11,12,13,14,17,21,22,24,25,26,27,28,29,
		33,34,37,39,40,41,42,44,45,46,47,51,52,54,55,56,57,59,
		63,64,67,69,70,71,72,74,75,76,81,82,83,84,85,86,87,88,89,
		90,91,92,93,99,101,102,103,104,105,106,107,108,109,110,111,116,
		124,125,126,132,133,134,135,136,137,141,142,
		154,155,156,165,166,168,169,170,
		184,185,186,187,188,189,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,
		211,212,217,218,219,225,227,228,229,230,231,232,233,234,235,236,237,238,239,
		241,242,250,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,271,272,
		280,282,283,284,285,286,287,288,289,290,291,293,294,295,296,297,298,299,301,302,310,311,312,313,314,315,
		316,317,318,319,320,321,322,325,327,334,335,336,348,349,351,352,360,361,362,363,364,365,366,378,379,380,381,382,390,391,392,394,396,420,421,422
	};

	glm::ivec2 mapSize = map->getMapSize();

	// Algoritmo DDA
	int N = std::max(abs(int(dx)), abs(int(dy)));

	if (N == 0)
		return true;  // Mismo tile

	// Recorrer la línea
	for (int step = 0; step <= N; step++)
	{
		float t = float(step) / float(N);
		float x = x0 + t * dx;
		float y = y0 + t * dy;

		int tileX = int(x);
		int tileY = int(y);

		// Verificar si estamos fuera del mapa
		if (tileX < 0 || tileX >= mapSize.x || tileY < 0 || tileY >= mapSize.y)
			return false;

		// Obtener el tile actual
		int currentTile = map->getTileAt(tileX, tileY);

		// Verificar si el tile es bloqueante (excepto el primer y último tile)
		if (step > 0 && step < N)
		{
			for (int i = 0; i < blockingTiles.size(); i++)
			{
				if (currentTile == blockingTiles[i])
					return false;  // Obstáculo encontrado
			}
		}
	}

	return true;  // Línea de visión despejada
}