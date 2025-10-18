#pragma once
#include "Item.h"

class Gun : public Item {
public:
	Gun(const glm::ivec2& position, ShaderProgram& shaderProgram);
	int getAmmo() const { return ammo; }
	void reload(int ammoCount) { ammo += ammoCount; }
	int getType() override;

private:
	int ammo;

};

