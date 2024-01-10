#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H
#include <Session.h>
#include <Component.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include <Color.h>
#include <Fonts.h>

class TextComponent : public Component
{
public:
    // Create a new instance of TextComponent and return it as a unique_ptr, add to session via session.add_component(std::move(text_component))
    // Note: Color alpha is ignored
    static std::unique_ptr<TextComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int max_width, int max_height, std::string text, Color color, Font f) {
        return std::unique_ptr<TextComponent>(new TextComponent(session, x, y, max_width, max_height, text, color, f));
    }
    void render() const override;
    void tick() {};
    ~TextComponent();
    std::string get_text() const { return text; }
    void set_text(std::string text);
protected:
    TextComponent(std::shared_ptr<Session> session, int x, int y, int max_width, int max_height, std::string text, Color color, Font f);
private:
    int max_width;
    int max_height;
    std::string text;
    SDL_Texture *tex;
    TTF_Font* font;
    Color color;
    int calculate_width(std::string text);
    void draw_text(std::string text);

};

#endif
