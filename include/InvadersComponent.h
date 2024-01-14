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

protected:
    InvadersComponent(std::shared_ptr<Session> session, int x, int y, int num_rows, int num_cols, int invader_width, int invader_height, int invader_spacing, std::shared_ptr<TextComponent> score_text)
        : Component(
              session, x, y, [&]()
              { return num_cols * (invader_width + invader_spacing) - invader_spacing; }(),
              [&]()
              { return num_rows * (invader_height + invader_spacing) - invader_spacing; }(),
              false),
          num_rows(num_rows), num_cols(num_cols),
          invader_width(invader_width), invader_height(invader_height), invader_spacing(invader_spacing), score_text(score_text)
    {
        create_invaders();
    }

private:
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