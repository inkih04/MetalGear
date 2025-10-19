#pragma once
#include "Projectile.h"
#include "Player.h"

class FireBall : public Projectile {

public:
	FireBall(const glm::ivec2& position, int direction, TileMap* currentMap, ShaderProgram& shaderProgram, Player *player);
	void hitTarget() override;
	bool getUser() override { return false; }
	~FireBall();

private:
	Player* player;

};
