#pragma once
#include "Item.h"


class MedPack : public Item {
public: 

	MedPack(const glm::ivec2& position, ShaderProgram& shaderProgram);
	~MedPack();

	void use(Player* player) override;
	int getType() override;
	bool destroyAfterUse() override;


};