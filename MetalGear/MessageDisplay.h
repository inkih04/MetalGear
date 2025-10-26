#ifndef _MESSAGE_DISPLAY_INCLUDE
#define _MESSAGE_DISPLAY_INCLUDE

#include "Sprite.h"
#include "Texture.h"
#include <string>

class MessageDisplay
{
public:
    MessageDisplay();
    ~MessageDisplay();

    void init(ShaderProgram& shaderProgram);
    void update(int deltaTime);
    void render();

    void showMessage(const std::string& imageName, int duration = 1500);

    bool isShowingMessage() const { return showing; }

private:
    Sprite* sprite;
    Texture texture;
    bool showing;
    int timeRemaining;
    std::string currentImage;
    ShaderProgram* program;
};

#endif // _MESSAGE_DISPLAY_INCLUDE
