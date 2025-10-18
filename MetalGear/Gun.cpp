#include "Gun.h"



Gun::Gun(const glm::ivec2& position, ShaderProgram& shaderProgram) {
	init(shaderProgram);
	this->position = position;
	sprite->setPosition(position);
	this->ammo = 0; 
}

int Gun::getType() {
	return GUN;
}