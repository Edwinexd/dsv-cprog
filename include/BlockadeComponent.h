#ifndef BLOCKADECOMPONENT_H
#define BLOCKADECOMPONENT_H
#include <Enemy.h>
#include "TextComponent.h"
#include "ImageComponent.h"

// Spelklass - Blockade härleds från Enemy
class BlockadeComponent : public Enemy {
public:
    static std::shared_ptr<BlockadeComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path);
    void kill() override;
    void tick() override;
    ~BlockadeComponent();
private:
    BlockadeComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path);
    std::shared_ptr<TextComponent> health_text;
    std::shared_ptr<ImageComponent> image_component;
};

#endif