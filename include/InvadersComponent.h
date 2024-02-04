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
#ifndef INVADERS_H
#define INVADERS_H
#include "Direction.h"
#include "Enemy.h"
#include <Spaceinvader.h>
#include <Color.h>
#include <MultipartRectangleTexture.h>
#include <TextComponent.h>
#include <Player.h>
#include <array>
#include <random>

// Spelklass - Huvudsakliga spellogiken, härleds från Component
// TODO: This file should have a corresponding .cpp file
class InvadersComponent : public Component
{
public:
    static std::shared_ptr<InvadersComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int num_rows, int num_cols, int invader_width, int invader_height, int invader_spacing, std::shared_ptr<TextComponent> score_text) {
        return std::shared_ptr<InvadersComponent>(new InvadersComponent(session, x, y, num_rows, num_cols, invader_width, invader_height, invader_spacing, score_text));
    }

    void on_remove(std::shared_ptr<Component> other);

    bool safe_to_shoot(unsigned col, unsigned row);


    void create_invaders();

    bool shoot_bottom_of_column(int col);

    void shoot_random_invader();

    void shoot_bottom_invaders();

    void tick() override;


    bool check_wall_collision();

    void update_direction();

    void render() const override
    {
    }
private:
    InvadersComponent(std::shared_ptr<Session> session, int x, int y, int num_rows, int num_cols, int invader_width, int invader_height, int invader_spacing, std::shared_ptr<TextComponent> score_text);
    unsigned int random_seed;
    unsigned int tick_count = 0;
    bool is_left = true;
    unsigned int num_rows;
    unsigned int num_cols;
    int invader_width;
    int invader_height;
    int invader_spacing;
    int total_invaders = 0;
    int alive_invaders = 0;
    Direction unit_vec[2] = {{1,0},{-1,0}};
    bool game_over = false;
    std::vector<std::vector<std::shared_ptr<Spaceinvader>>> invaders;
    std::shared_ptr<TextComponent> score_text;
};

#endif