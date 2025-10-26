#pragma once
#include "Projectile.h"
#include "Player.h"

class BossAtack : public Projectile {

public:
	BossAtack(const glm::ivec2& position, int direction, TileMap* currentMap, ShaderProgram& shaderProgram, Player* player);
	void hitTarget() override;
	bool getUser() override { return false; }
	~BossAtack();

private:
	Player* player;

};
