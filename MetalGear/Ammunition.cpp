#include "Ammunition.h"
#include "Player.h"
#include "AudioManager.h"

Ammunition::Ammunition(const glm::ivec2& position, ShaderProgram& shaderProgram) {
	init(shaderProgram);
	this->position = position;
	sprite->setPosition(position);
}

Ammunition::~Ammunition() {
	if (sprite != nullptr) delete sprite;
}

bool Ammunition::destroyAfterUse() {
	return true;
}
void Ammunition::use(Player* player) {
	AudioManager::instance().playSound("sound_reload", 10.0);
	player->reloadGun(3);
}
int Ammunition::getType() {
	return BULLETS;
}

