#pragma once
#pragma once
#include "Item.h"


class Key : public Item {
public:

	Key(const glm::ivec2& position, ShaderProgram& shaderProgram);
	~Key();

	void use(Player* player) override;
	int getType() override;
	bool destroyAfterUse() override;


};