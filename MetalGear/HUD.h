#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE

#include "Sprite.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

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

    Texture hudTexture;
    Texture heartTexture;
    Texture fistTexture;
    Texture gunTexture;      

    Sprite* hudSprite;
    Sprite* heartSprite;
    Sprite* fistSprite;
    Sprite* gunSprite;       

    ShaderProgram* texProgram;

    glm::vec2 hudPosition;
    int maxHearts;
};

#endif // _HUD_INCLUDE