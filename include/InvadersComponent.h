#ifndef INVADERS_H
#define INVADERS_H
#include "Direction.h"
#include "Enemy.h"
#include <Spaceinvader.h>
#include <TextComponent.h>
#include <Player.h>
#include <array>

// Spelklass - Huvudsakliga spellogiken, härleds från Component
// TODO: This file should have a corresponding .cpp file
class InvadersComponent : public Component
{
public:
    static std::shared_ptr<InvadersComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int num_rows, int num_cols, int invader_width, int invader_height, int invader_spacing, std::shared_ptr<TextComponent> score_text) {
        return std::shared_ptr<InvadersComponent>(new InvadersComponent(session, x, y, num_rows, num_cols, invader_width, invader_height, invader_spacing, score_text));
    }

    void on_remove(std::shared_ptr<Component> other) {
        if (auto invader = std::dynamic_pointer_cast<Spaceinvader>(other)) {
            for (unsigned col = 0; col < num_cols; col++) {
                for (unsigned row = 0; row < num_rows; row++) {
                    if (invaders[col][row] == invader) {
                        invaders[col][row] = nullptr;
                        alive_invaders--;
                        if (game_over) {
                            return;
                        }
                        session->play_sound("sounds/score.wav", 0);
                        return;
                    }
                }
            }
        } else if (auto player = std::dynamic_pointer_cast<Player>(other)) {
            game_over = true;
            // TODO: Spawn death beam or some other end effect
        }
    }

    void create_invaders()
    {
        invaders.resize(num_cols, std::vector<std::shared_ptr<Spaceinvader>>(num_rows));

        for (unsigned row = 0; row < num_rows; row++)
        {
            for (unsigned col = 0; col < num_cols; col++)
            {
                int x = col * (invader_width + invader_spacing);
                int y = row * (invader_height + invader_spacing);
                auto invader = Spaceinvader::create_instance(session, x, y, invader_width, invader_height, 1, "images/alive.png", "images/dead.png");
                session->add_component(invader);
                invaders[col][row] = invader;
                total_invaders++;
                alive_invaders++;
            }
        }
    }

    bool shoot_bottom_of_column(int col)
    {
        
        for (int row = num_rows - 1; row >= 0; row--)
        {
            if (invaders[col][row].get() != nullptr)
            {
                auto invader = invaders[col][row];
                if (invader->is_dead())
                {
                    continue;
                }
                invader->shoot();
                return true;
            }
        }
        return false;
    }

    void shoot_random_invader()
    {
        std::vector<unsigned> columns;
        for (unsigned col = 0; col < num_cols; col++)
        {
            if (!invaders[col].empty())
            {
                columns.push_back(col);
            }
        }
        if (columns.empty())
        {
            return;
        }
        // Shuffle columns
        std::random_shuffle(columns.begin(), columns.end());
        for (auto col : columns)
        {
            if (shoot_bottom_of_column(col))
            {
                return;
            }
        }
    }

    void shoot_bottom_invaders()
    {
        for (unsigned col = 0; col < num_cols; col++)
        {
            if (!invaders[col].empty())
            {
                for (unsigned row = num_rows - 1; row >= 0; row--)
                {
                    if (invaders[col][row] != nullptr)
                    {
                        // Guaranteed to not be nullptr by tick
                        auto invader = invaders[col][row];
                        invader->shoot();
                        break;
                    }
                }
            }
        }
    }

    void tick() override
    {
        tick_count++;
        if (alive_invaders == 0 && !game_over)
        {
            score_text->set_text("You win!");
            return;
        }

        check_wall_collision();

        if (tick_count % 100 == 0 || (game_over && tick_count % 10 == 0))
        {
            shoot_random_invader();
        }
        if (game_over)
        {
            score_text->set_text("Game over!");
        } else {
            score_text->set_text("Score: " + std::to_string(total_invaders - alive_invaders));
        }
    }


    bool check_wall_collision()
    {
        if(is_left)
        {
            for(unsigned col = 0; col < num_cols; ++col)
            {
                for(unsigned row = 0; row < num_rows; ++row)
                {
                    auto current_invader = invaders[col][row];
                    if(current_invader != nullptr)
                    {
                        if(!current_invader->is_dead())
                        {
                            
                            if(current_invader->get_x() <= invader_spacing*2)
                            {
                                is_left = false;
                                update_direction();
                                return true;

                            }

                        }
                    }
                }
                
            }
        }
        else {
            for(int col = (int) num_cols - 1; col >= 0 ; --col)
            {

                for(unsigned row = 0; row < num_rows; row++)
                {
                    auto current_invader = invaders[col][row];
                    if(current_invader != nullptr)
                    {
                        if(!current_invader->is_dead())
                        {                            
                            if(current_invader->get_x() + invader_width >= session->get_window_data().get_width() - invader_spacing*2)
                            {
                                is_left = true;
                                update_direction();
                                return true;

                            }

                        }
                    }
                }

            }
        }
        return false;

    }

    void update_direction()
    {
        for (unsigned col = 0; col < num_cols; ++col)
        {
            if (!invaders[col].empty())
            {
                for (unsigned row = 0; row < num_rows; ++row)
                {
                    if (invaders[col][row] != nullptr)
                    {
                        // Guaranteed to not be nullptr by tick
                        auto invader = invaders[col][row];
                        invader->set_direction(unit_vec[is_left ? 1 : 0]);
                    }
                }
            }
        }
    }

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