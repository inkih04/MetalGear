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

    // Animaci�n coraz�n completo
    heartSprite->setAnimationSpeed(0, 1);
    heartSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));

    // Animaci�n medio coraz�n
    heartSprite->setAnimationSpeed(1, 1);
    heartSprite->addKeyframe(1, glm::vec2(0.25f, 0.0f));

    // Cargar textura del pu�o
    fistTexture.loadFromFile("hud/pu�o.png", TEXTURE_PIXEL_FORMAT_RGBA);
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

    // Cargar textura de n�meros (NUEVO)
    // La imagen tiene 10 d�gitos (1,2,3,4,5,6,7,8,9,0) cada uno de 16x16
    // Total de la imagen: 160x16 pixels
    numbersTexture.loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
    numberSprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.1f, 1.0f), &numbersTexture, &shaderProgram);
    numberSprite->setNumberAnimations(10);

    // Configurar animaci�n para cada d�gito (1,2,3,4,5,6,7,8,9,0)
    for (int i = 0; i < 10; i++) {
        numberSprite->setAnimationSpeed(i, 1);
        numberSprite->addKeyframe(i, glm::vec2(i * 0.1f, 0.0f));
    }

    // Posici�n del HUD
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
    float slot2X = 218.0f;
    float slotY = 7.5f;

    // Verificar si el jugador tiene el arma equipada
    bool hasGun = player->hasGun();
    bool isGunEquipped = player->isGunEquipped();

    if (hasGun && isGunEquipped) {
        // Mostrar el sprite de la pistola
        gunSprite->setPosition(glm::vec2(slot1X, slotY));
        gunSprite->render();

        // Renderizar el n�mero de balas en la esquina inferior derecha
        renderAmmoCount(player->getAmmo(), slot1X, slotY);
    }
    else {
        // Mostrar el sprite del pu�o (sin n�mero)
        fistSprite->setPosition(glm::vec2(slot1X, slotY));
        fistSprite->render();
    }
}

void HUD::renderAmmoCount(int ammo, float x, float y)
{
    std::string ammoStr = std::to_string(ammo);
    float digitSpacing = 6.0f;  // Espacio entre d�gitos (ajusta si es necesario)

    // Posici�n fija para el d�gito de las unidades (esquina inferior derecha del slot)
    float unitsX = x + 9.0f;   // Ajusta para que est� en el borde derecho
    float numberY = y + 8.0f;  // Ajusta para la parte inferior

    // Renderizar de derecha a izquierda (desde las unidades hacia las decenas/centenas)
    for (int i = ammoStr.length() - 1; i >= 0; i--) {
        char c = ammoStr[i];
        int digit;

        // Mapear el car�cter al �ndice de animaci�n
        // Tu imagen tiene: 1,2,3,4,5,6,7,8,9,0
        if (c == '0') {
            digit = 9;  // El 0 est� en la �ltima posici�n
        }
        else {
            digit = c - '1';  // '1' -> 0, '2' -> 1, etc.
        }

        // Calcular posici�n: las unidades est�n en unitsX, las decenas a la izquierda, etc.
        int digitIndex = ammoStr.length() - 1 - i;
        float posX = unitsX - (digitIndex * digitSpacing);

        // Cambiar a la animaci�n del d�gito correspondiente
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
}