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

    // Cargar textura de la pistola (NUEVO)
    gunTexture.loadFromFile("hud/pistola.png", TEXTURE_PIXEL_FORMAT_RGBA);
    gunSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &gunTexture, &shaderProgram);
    gunSprite->setNumberAnimations(1);
    gunSprite->setAnimationSpeed(0, 1);
    gunSprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
    gunSprite->changeAnimation(0);

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
    float slot2X = 218.0f;
    float slotY = 7.5f;

    // Verificar si el jugador tiene el arma equipada
    bool hasGun = player->hasGun();
    bool isGunEquipped = player->isGunEquipped();

    if (hasGun && isGunEquipped) {
        // Mostrar el sprite de la pistola
        gunSprite->setPosition(glm::vec2(slot1X, slotY));
        gunSprite->render();

        // Renderizar el número de balas (NUEVO)
        renderAmmoCount(player->getAmmo(), slot1X, slotY);
    }
    else {
        // Mostrar el sprite del puño
        fistSprite->setPosition(glm::vec2(slot1X, slotY));
        fistSprite->render();
    }
}

void HUD::renderAmmoCount(int ammo, float x, float y)
{
    // Por ahora, simplemente imprime en consola
    // Para una implementación completa necesitarías un sistema de renderizado de texto
    // o sprites numéricos

    // Si quieres implementarlo con sprites:
    // 1. Crea una textura "hud/numeros.png" con los dígitos 0-9
    // 2. En init(), carga esa textura y crea un sprite para números
    // 3. Aquí, convierte 'ammo' a string y renderiza cada dígito

    // Ejemplo básico (requiere implementación adicional):
    // std::string ammoStr = std::to_string(ammo);
    // float currentX = x + 10.0f;
    // for (char c : ammoStr) {
    //     int digit = c - '0';
    //     // Actualizar coordenadas de textura del sprite numérico
    //     // numberSprite->setTexCoord(digit * 0.1f, 0.0f);  // Asumiendo 10 dígitos en fila
    //     // numberSprite->setPosition(glm::vec2(currentX, y + 12.0f));
    //     // numberSprite->render();
    //     // currentX += 6.0f;  // Espacio entre dígitos
    // }
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
}