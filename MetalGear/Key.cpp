#include "Key.h"
#include "Player.h"
#include "AudioManager.h"

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
    AudioManager::instance().playSound("sound_button");
    player->openDor();
}

int Key::getType()
{
    return KEY;
}