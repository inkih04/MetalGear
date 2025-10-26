#include "MedPack.h"
#include "Player.h"
#include "AudioManager.h"

MedPack::MedPack(const glm::ivec2& position, ShaderProgram& shaderProgram) {
	init(shaderProgram);
	this->position = position;
	sprite->setPosition(position);
}

MedPack::~MedPack() {
	if (sprite != nullptr) delete sprite;
}

bool MedPack::destroyAfterUse() {
	return true;
}
void MedPack::use(Player* player) {
	AudioManager::instance().playSound("sound_heal", 10.0);
	player->heal(5);
}
int MedPack::getType() {
	return LIFE;
}

