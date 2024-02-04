/* 
dsv-cprog-space-invaders - A space invaders inspired shooter written in C++ with SDL2
Copyright (C) 2024 Edwin Sundberg and Erik Lind Gou-Said

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef BLOCKADECOMPONENT_H
#define BLOCKADECOMPONENT_H
#include <Enemy.h>
#include <TextComponent.h>
#include <ImageComponent.h>

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
};

#endif