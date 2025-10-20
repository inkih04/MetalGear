#include "MedPack.h"
#include "Player.h"

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
	player->heal(3);
}
int MedPack::getType() {
	return LIFE;
}

