#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H
#include <Session.h>
#include <Component.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>

class TextComponent : public Component
{
public:
    static std::shared_ptr<TextComponent> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, std::string text) {
        return std::shared_ptr<TextComponent>(new TextComponent(session, x, y, w, h, text));
    }
    void render() const override;
    void tick() {};
    ~TextComponent();
    std::string getText() const { return text; }
    void setText(std::string text);
protected:
    TextComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, std::string text);
private:
    std::string text;
    SDL_Texture *tex;
    TTF_Font* font;

};

#endif
