#pragma once
#include "Projectile.h"

class Bullet : public Projectile {

	public:
		Bullet(int hitBoxOffset, const glm::ivec2& position, int direction, TileMap* currentMap, ShaderProgram& shaderProgram);
		bool getUser() override { return true; }
		void hitTarget() override;
		~Bullet();

};
