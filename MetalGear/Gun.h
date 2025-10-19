#pragma once
#include "Item.h"
#include "Bullet.h"



class Gun : public Item {
public:
	Gun(const glm::ivec2& position, ShaderProgram& shaderProgram);
	int getAmmo() const { return ammo; }
	void reload(int ammoCount) { ammo += ammoCount; }
	int getType() override;
	bool canShoot();
	void shoot(const glm::ivec2& playerPos, int direction, TileMap* currentMap);
	void update(int deltaTime) override;
	void renderGun();



private:
	vector<Bullet*> bullets;
	int ammo;
	int fireRate;
	int lastShotTime;
	ShaderProgram* s;
};

