#pragma once
#include "Item.h"


class Ammunition : public Item {
public:

	Ammunition(const glm::ivec2& position, ShaderProgram& shaderProgram);
	~Ammunition();

	void use(Player* player) override;
	int getType() override;
	bool destroyAfterUse() override;


};