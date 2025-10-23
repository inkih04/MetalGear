#include "HUD.h"
#include "Player.h"
#include <iostream>
#include <GL/glew.h>
#include <string>

void HUD::init(ShaderProgram& shaderProgram)
{
    texProgram = &shaderProgram;
    maxHearts = 5;

    // Cargar textura del marco del HUD
    hudTexture.loadFromFile("hud/hud.png", TEXTURE_PIXEL_FORMAT_RGBA);
    hudSprite = Sprite::createSprite(glm::ivec2(240, 160), glm::vec2(1.0f, 1.0f), &hudTexture, &shaderProgram);
    hudSprite->setNumberAnimations(1);
    hudSprite->setAnimationSpeed(0, 1);
    hudSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
    hudSprite->changeAnimation(0);

    // Cargar textura de corazones
    heartTexture.loadFromFile("hud/corazon.png", TEXTURE_PIXEL_FORMAT_RGBA);
    heartSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25f, 1.0f), &heartTexture, &shaderProgram);
    heartSprite->setNumberAnimations(2);

    // Animación corazón completo
    heartSprite->setAnimationSpeed(0, 1);
    heartSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));

    // Animación medio corazón
    heartSprite->setAnimationSpeed(1, 1);
    heartSprite->addKeyframe(1, glm::vec2(0.25f, 0.0f));

    // Cargar textura del puño
    fistTexture.loadFromFile("hud/puño.png", TEXTURE_PIXEL_FORMAT_RGBA);
    fistSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &fistTexture, &shaderProgram);
    fistSprite->setNumberAnimations(1);
    fistSprite->setAnimationSpeed(0, 1);
    fistSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
    fistSprite->changeAnimation(0);

    // Cargar textura de la pistola
    gunTexture.loadFromFile("hud/pistola.png", TEXTURE_PIXEL_FORMAT_RGBA);
    gunSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &gunTexture, &shaderProgram);
    gunSprite->setNumberAnimations(1);
    gunSprite->setAnimationSpeed(0, 1);
    gunSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
    gunSprite->changeAnimation(0);

    // Cargar textura de números
    numbersTexture.loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
    numberSprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.1f, 1.0f), &numbersTexture, &shaderProgram);
    numberSprite->setNumberAnimations(10);

    // Configurar animación para cada dígito (1,2,3,4,5,6,7,8,9,0)
    for (int i = 0; i < 10; i++) {
        numberSprite->setAnimationSpeed(i, 1);
        numberSprite->addKeyframe(i, glm::vec2(i * 0.1f, 0.0f));
    }

    // Cargar textura de cura
    cureTexture.loadFromFile("hud/cura.png", TEXTURE_PIXEL_FORMAT_RGBA);
    cureSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &cureTexture, &shaderProgram);
    cureSprite->setNumberAnimations(1);
    cureSprite->setAnimationSpeed(0, 1);
    cureSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
    cureSprite->changeAnimation(0);

    // Cargar textura de munición
    ammoTexture.loadFromFile("hud/ammo.png", TEXTURE_PIXEL_FORMAT_RGBA);
    ammoSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &ammoTexture, &shaderProgram);
    ammoSprite->setNumberAnimations(1);
    ammoSprite->setAnimationSpeed(0, 1);
    ammoSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
    ammoSprite->changeAnimation(0);

    // Cargar textura de llave
    keyTexture.loadFromFile("hud/button.png", TEXTURE_PIXEL_FORMAT_RGBA);
    keySprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &keyTexture, &shaderProgram);
    keySprite->setNumberAnimations(1);
    keySprite->setAnimationSpeed(0, 1);
    keySprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
    keySprite->changeAnimation(0);

    // Posición del HUD
    hudPosition = glm::vec2(0.0f, 0.0f);

    std::cout << "HUD initialized successfully" << std::endl;
}

void HUD::render(int playerHealth, Player* player)
{
    // Renderizar el marco del HUD
    hudSprite->setPosition(hudPosition);
    hudSprite->render();

    // Renderizar los corazones
    renderHearts(playerHealth);

    // Renderizar los slots de inventario
    renderInventorySlots(player);
}

void HUD::renderHearts(int health)
{
    float startX = 10.0f;
    float startY = 6.5f;
    float spacing = 16.0f;

    for (int i = 0; i < maxHearts; i++)
    {
        int healthForThisHeart = health - (i * 2);

        if (healthForThisHeart >= 2) {
            heartSprite->changeAnimation(0);
            heartSprite->setPosition(glm::vec2(startX + i * spacing, startY));
            heartSprite->render();
        }
        else if (healthForThisHeart == 1) {
            heartSprite->changeAnimation(1);
            heartSprite->setPosition(glm::vec2(startX + i * spacing, startY));
            heartSprite->render();
        }
    }
}

void HUD::renderInventorySlots(Player* player)
{
    float slot1X = 183.5f;
    float slotY = 7.5f;

    // SLOT 1: Arma (pistola o puño)
    bool hasGun = player->hasGun();
    bool isGunEquipped = player->isGunEquipped();

    if (hasGun && isGunEquipped) {
        gunSprite->setPosition(glm::vec2(slot1X, slotY));
        gunSprite->render();
        renderAmmoCount(player->getAmmo(), slot1X, slotY);
    }
    else {
        fistSprite->setPosition(glm::vec2(slot1X, slotY));
        fistSprite->render();
    }

    // SLOT 2: Item actual del inventario
    renderCurrentItem(player);
}

void HUD::renderAmmoCount(int ammo, float x, float y)
{
    std::string ammoStr = std::to_string(ammo);
    float digitSpacing = 6.0f;

    float unitsX = x + 9.0f;
    float numberY = y + 7.7f;

    for (int i = ammoStr.length() - 1; i >= 0; i--) {
        char c = ammoStr[i];
        int digit;

        if (c == '0') {
            digit = 9;
        }
        else {
            digit = c - '1';
        }

        int digitIndex = ammoStr.length() - 1 - i;
        float posX = unitsX - (digitIndex * digitSpacing);

        numberSprite->changeAnimation(digit);
        numberSprite->setPosition(glm::vec2(posX, numberY));
        numberSprite->render();
    }
}

void HUD::renderCurrentItem(Player* player)
{
    float slot2X = 208.0f;
    float slotY = 7.1f;

    // Si no hay items, no renderizar nada
    if (player->getCurrentItem() == nullptr) {
        return;
    }

    Item* currentItem = player->getCurrentItem();
    int itemType = currentItem->getType();

    // Renderizar el sprite correspondiente según el tipo de item
    if (itemType == LIFE) {
        // Renderizar sprite de cura
        cureSprite->setPosition(glm::vec2(slot2X, slotY));
        cureSprite->render();

        // Renderizar cantidad
        renderItemCount(player->getItemCount(currentItem), slot2X, slotY);
    }
    else if (itemType == BULLETS) {
        // Renderizar sprite de munición
        ammoSprite->setPosition(glm::vec2(slot2X, slotY));
        ammoSprite->render();

        // Renderizar cantidad
        renderItemCount(player->getItemCount(currentItem), slot2X, slotY);
    }
    else if (itemType == KEY) {
        // Renderizar sprite de llave (sin cantidad)
        keySprite->setPosition(glm::vec2(slot2X, slotY));
        keySprite->render();
    }
}

void HUD::renderItemCount(int count, float x, float y)
{
    std::string countStr = std::to_string(count);
    float digitSpacing = 6.0f;

    float unitsX = x + 9.5f;
    float numberY = y + 8.0f;

    for (int i = countStr.length() - 1; i >= 0; i--) {
        char c = countStr[i];
        int digit;

        if (c == '0') {
            digit = 9;
        }
        else {
            digit = c - '1';
        }

        int digitIndex = countStr.length() - 1 - i;
        float posX = unitsX - (digitIndex * digitSpacing);

        numberSprite->changeAnimation(digit);
        numberSprite->setPosition(glm::vec2(posX, numberY));
        numberSprite->render();
    }
}

void HUD::free()
{
    if (hudSprite != nullptr)
        delete hudSprite;
    if (heartSprite != nullptr)
        delete heartSprite;
    if (fistSprite != nullptr)
        delete fistSprite;
    if (gunSprite != nullptr)
        delete gunSprite;
    if (numberSprite != nullptr)
        delete numberSprite;
    if (cureSprite != nullptr)
        delete cureSprite;
    if (ammoSprite != nullptr)
        delete ammoSprite;
    if (keySprite != nullptr)
        delete keySprite;
}