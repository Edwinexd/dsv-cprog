#ifndef INVADERS_H
#define INVADERS_H
#include "Direction.h"
#include "Enemy.h"
#include "Session.h"
#include <Spaceinvader.h>
#include <TextComponent.h>
#include <array>

// TODO: This file should have a corresponding .cpp file
class InvadersComponent : public Component
{
public:
    static std::shared_ptr<InvadersComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int num_rows, int num_cols, int invader_width, int invader_height, int invader_spacing, std::shared_ptr<TextComponent> score_text) {
        return std::shared_ptr<InvadersComponent>(new InvadersComponent(session, x, y, num_rows, num_cols, invader_width, invader_height, invader_spacing, score_text));
    }

    void on_remove(std::shared_ptr<Component> other) {
        if (auto invader = std::dynamic_pointer_cast<Spaceinvader>(other)) {
            for (int col = 0; col < num_cols; col++) {
                for (int row = 0; row < num_rows; row++) {
                    if (invaders[col][row] == invader) {
                        invaders[col][row] = nullptr;
                        alive_invaders--;
                        session->play_sound("sounds/score.wav", 0);
                        return;
                    }
                }
            }
        }
    }

    void create_invaders()
    {
        invaders.resize(num_cols, std::vector<std::shared_ptr<Spaceinvader>>(num_rows));

        for (int row = 0; row < num_rows; row++)
        {
            for (int col = 0; col < num_cols; col++)
            {
                int x = col * (invader_width + invader_spacing);
                int y = row * (invader_height + invader_spacing);
                auto invader = Spaceinvader::create_instance(session, x, y, invader_width, invader_height, 1, "images/alive.png", "images/dead.png", 1);
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
        std::vector<int> columns;
        for (int col = 0; col < num_cols; col++)
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
        for (int col = 0; col < num_cols; col++)
        {
            if (!invaders[col].empty())
            {
                for (int row = num_rows - 1; row >= 0; row--)
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

        
        const WindowInformation&  window = session.get_window_data()
        tick_count++;
        if (alive_invaders == 0)
        {
            score_text->set_text("You win!");
            return;
        }

        bool wall_collide = check_wall_collision();

        if (tick_count % 100 == 0)
        {
            if (!wall_collide)
            {
                if(tick_count % 200 == 0)
                {
                    // reverse direction, if active_direction is even we add 1, if it is odd we subtract 1
                    is_left = !is_left ?  true : false;
                
                }
                else {
                    srand(random_seed + tick_count);
                    is_left = rand() % 2;
            
                }
            }
            shoot_random_invader();

        }
        score_text->set_text("Score: " + std::to_string(total_invaders - alive_invaders));
    }


    bool check_wall_collision()
    {
        if(is_left)
        {
            for(int i = 0; i < num_cols; i++)
            {
                
            }
        }
        else {
            for(int i = num_cols - 1; i >= 0 ; i--)
            {

            }
        }
        return false;

    }

    void update_direction()
    {
        for (int col = 0; col < num_cols; col++)
        {
            if (!invaders[col].empty())
            {
                for (int row = num_rows - 1; row >= 0; row--)
                {
                    if (invaders[col][row] != nullptr)
                    {
                        // Guaranteed to not be nullptr by tick
                        auto invader = invaders[col][row];
                        invader->set_direction(unit_vec[is_left]);
                        
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
    Direction unit_vec[2] = {{1,0},{0,1}};
    std::vector<std::vector<std::shared_ptr<Spaceinvader>>> invaders;
    std::shared_ptr<TextComponent> score_text;
};

#endif