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
#ifndef MULTIPARTCOMPONENT_H
#define MULTIPARTCOMPONENT_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>

// Spelmotorklass - Komponent som kan ha flera olika texturer och byta mellan dem
class MultipartComponent : public Component
{
public:
    static std::shared_ptr<MultipartComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d);
    void render() const override;
    void tick() {
        Component::tick();
    };
    void add_texture(std::shared_ptr<MultipartTexture> tex);
    void remove_texture(size_t index);
    void remove_texture(std::shared_ptr<MultipartTexture> tex);
    void set_texture(size_t index);
    void next_texture();
    std::size_t get_active_texture() const {
        return current_texture;
    }
    ~MultipartComponent();
protected:
    MultipartComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d);
private:
    std::vector<std::shared_ptr<MultipartTexture>> textures;
    std::size_t current_texture;
};

#endif