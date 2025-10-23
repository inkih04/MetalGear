#include "MessageDisplay.h"
#include <iostream>

MessageDisplay::MessageDisplay()
{
    sprite = nullptr;
    showing = false;
    timeRemaining = 0;
    program = nullptr;
}

MessageDisplay::~MessageDisplay()
{
    if (sprite != nullptr)
        delete sprite;
}

void MessageDisplay::init(ShaderProgram& shaderProgram)
{
    program = &shaderProgram;
    // Creamos un sprite que ocupa toda la pantalla (240x160)
    sprite = Sprite::createSprite(glm::ivec2(240, 160), glm::vec2(1.f, 1.f), &texture, &shaderProgram);
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 1);
    sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
    sprite->changeAnimation(0);
    sprite->setPosition(glm::vec2(0.f, 0.f));
}

void MessageDisplay::update(int deltaTime)
{
    if (showing)
    {
        timeRemaining -= deltaTime;
        if (timeRemaining <= 0)
        {
            showing = false;
            std::cout << "Message hidden" << std::endl;
        }
    }
}

void MessageDisplay::render()
{
    if (showing && sprite != nullptr)
    {
        sprite->render();
    }
}

void MessageDisplay::showMessage(const std::string& imageName, int duration)
{
    if (currentImage != imageName)
    {
        // Cargar nueva textura solo si es diferente
        std::string path = "images/" + imageName + ".png";
        texture.loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);

        // Recrear sprite con la nueva textura
        if (sprite != nullptr)
            delete sprite;

        sprite = Sprite::createSprite(glm::ivec2(240, 160), glm::vec2(1.f, 1.f), &texture, program);
        sprite->setNumberAnimations(1);
        sprite->setAnimationSpeed(0, 1);
        sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
        sprite->changeAnimation(0);
        sprite->setPosition(glm::vec2(0.f, 0.f));

        currentImage = imageName;
    }

    showing = true;
    timeRemaining = duration;
    std::cout << "Showing message: " << imageName << " for " << duration << "ms" << std::endl;
}