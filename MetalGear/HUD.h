#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE

#include "Sprite.h"
#include "Texture.h"
#include "ShaderProgram.h"

class Player;

class HUD
{
public:
    void init(ShaderProgram& shaderProgram);
    void render(int playerHealth, Player* player);
    void free();

private:
    void renderHearts(int health);
    void renderInventorySlots(Player* player);
    void renderAmmoCount(int ammo, float x, float y);
    void renderCurrentItem(Player* player);
    void renderItemCount(int count, float x, float y);

    ShaderProgram* texProgram;
    glm::vec2 hudPosition;
    int maxHearts;

    // HUD frame
    Texture hudTexture;
    Sprite* hudSprite;

    // Hearts
    Texture heartTexture;
    Sprite* heartSprite;

    // Weapons
    Texture fistTexture;
    Sprite* fistSprite;

    Texture gunTexture;
    Sprite* gunSprite;

    // Numbers
    Texture numbersTexture;
    Sprite* numberSprite;

    // Items
    Texture cureTexture;
    Sprite* cureSprite;

    Texture ammoTexture;
    Sprite* ammoSprite;

    Texture keyTexture;
    Sprite* keySprite;
};

#endif // _HUD_INCLUDE