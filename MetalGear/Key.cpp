#include "Key.h"
#include "Player.h"

Key::Key(const glm::ivec2& position, ShaderProgram& shaderProgram)
{
    init(shaderProgram);
    this->position = position;
    sprite->setPosition(position);
}

Key::~Key()
{
    if (sprite != nullptr)
        delete sprite;
}

bool Key::destroyAfterUse()
{
    return true;
}

void Key::use(Player* player)
{
    player->openDor();
}

int Key::getType()
{
    return KEY;
}