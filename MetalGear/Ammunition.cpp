#include "Ammunition.h"
#include "Player.h"

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
	player->reloadGun(3);
}
int Ammunition::getType() {
	return BULLETS;
}

