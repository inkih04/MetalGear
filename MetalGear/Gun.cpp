#include "Gun.h"
#include <iostream>
#include "TileMap.h"
#include "AudioManager.h"



Gun::Gun(const glm::ivec2& position, ShaderProgram& shaderProgram) {
	init(shaderProgram);
	s = &shaderProgram;
	this->position = position;
	sprite->setPosition(position);
	this->ammo = 5; 
	this->fireRate = 1000;
	this->lastShotTime = fireRate;
}

bool Gun::canShoot()
{
	return lastShotTime >= fireRate && ammo > 0;
}

void Gun::shoot(const glm::ivec2& playerPos, int direction, TileMap* currentMap)
{
	if (!canShoot())
		return;
	AudioManager::instance().playSound("sound_shot");
	int hitBoxOfsset = 0;

	if (playerPos.y < (currentMap->getMapSize().y * currentMap->getTileSize())/3) {
		hitBoxOfsset = 20;
	}


	Bullet* newBullet = new Bullet(hitBoxOfsset, playerPos, direction, currentMap, *s);
	bullets.push_back(newBullet);
	--ammo;
	lastShotTime = 0;
}

void Gun::update(int deltaTime)
{
	lastShotTime += deltaTime;

	for (auto it = bullets.begin(); it != bullets.end(); ) {
		(*it)->update(deltaTime);

		if (!(*it)->isActive()) {
			delete* it;
			it = bullets.erase(it);
		}
		else {
			++it;
		}
	}
}

void Gun::renderGun()
{
	for (auto bullet : bullets)
		bullet->render();

}

int Gun::getType() {
	return GUN;
}