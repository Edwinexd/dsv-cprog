#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H
#include <Component.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>

class TextComponent : public Component
{
public:
    static std::shared_ptr<TextComponent> createInstance(int x, int y, int w, int h, std::string text) {
        return std::shared_ptr<TextComponent>(new TextComponent(x, y, w, h, text));
    }
    void render() const override;
    void tick() {};
    ~TextComponent();
    std::string getText() const { return text; }
    void setText(std::string text);
protected:
    TextComponent(int x, int y, int w, int h, std::string text);
private:
    std::string text;
    SDL_Texture *tex;
    TTF_Font* font;

};

#endif
