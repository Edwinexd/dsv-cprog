#ifndef INVADERS_H
#define INVADERS_H
#include <Spaceinvader.h>
#include <Color.h>
#include "MultipartRectangleTexture.h"
#include <TextComponent.h>

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

    bool safe_to_shoot(int col, int row)
    {
        // Since rows move at different speeds and in different directions
        // we need to check if there effectively is a row in front of us
        // if there is, we can't shoot
        if (row == num_rows - 1)
        {
            return true;
        }
        auto invader = invaders[col][row];
        if (invader.get() == nullptr)
        {
            return true;
        }
        if (invader->is_dead())
        {
            return true;
        }

        int laser_dy = 1;
        int laser_x = invader->get_x() + (invader->get_width() / 2);
        int laser_y = invader->get_y() + invader->get_height();

        // check all components in front of us to see if they are in the way or are going to be in the way before
        // the laser is clear of the invaders rect
        // we assume that all entities below us are moving +-2 pixels per tick in x-direction
        int ticks_to_clear = (get_rect().y + get_rect().h - laser_y) / laser_dy;
        // TODO: This needs to be changed so we can draw as a small of a romb hitbox as possible
        // will need to make spaceinvader movement deterministic
        int ticks_to_clear_x = ticks_to_clear * 2;
        int ticks_to_clear_y = ticks_to_clear * laser_dy;
        int left_x_bound = laser_x - ticks_to_clear_x;
        int right_x_bound = laser_x + ticks_to_clear_x;
        int top_y_bound = laser_y;
        int bottom_y_bound = get_rect().y + get_rect().h;
        // Draw multipart component with the dimensions above
        std::shared_ptr<MultipartComponent> multipart = MultipartComponent::create_instance(session, left_x_bound, top_y_bound, right_x_bound - left_x_bound, bottom_y_bound - top_y_bound, false, {0, 0});
        auto multipartRectangle = MultipartRectangleTexture::create_instance(session, right_x_bound - left_x_bound, bottom_y_bound - top_y_bound, Color(255, 0, 0, 128));
        multipart->add_texture(multipartRectangle);
        session->add_component(multipart);

        // check if there is a component in the way of all components below us
        for (int r = row + 1; r < num_rows; r++)
        {
            for (int c = 0; c < num_cols; c++)
            {
                auto other_invader = invaders[c][r];
                if (other_invader.get() == nullptr)
                {
                    continue;
                }
                if (other_invader->is_dead())
                {
                    continue;
                }
                if (other_invader->get_x() + other_invader->get_width() < left_x_bound)
                {
                    continue;
                }
                if (other_invader->get_x() > right_x_bound)
                {
                    continue;
                }
                if (other_invader->get_y() + other_invader->get_height() < top_y_bound)
                {
                    continue;
                }
                if (other_invader->get_y() > bottom_y_bound)
                {
                    continue;
                }
                std::cout << "Can't shoot, invader " << col << "," << row << " is in the way!" << std::endl;
                return false;
            }
        }
        return true;
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
                auto invader = Spaceinvader::create_instance(session, x + get_x(), y + get_y(), invader_width, invader_height, 1, "images/alive.png", "images/dead.png", 1);
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
                if (!safe_to_shoot(col, row))
                {
                    return false;
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
        tick_count++;
        if (alive_invaders == 0)
        {
            score_text->set_text("You win!");
            return;
        }
        if (tick_count % 100 == 0)
        {
            shoot_random_invader();
        }
        score_text->set_text("Score: " + std::to_string(total_invaders - alive_invaders));
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
    int tick_count = 0;
    int num_rows;
    int num_cols;
    int invader_width;
    int invader_height;
    int invader_spacing;
    int total_invaders = 0;
    int alive_invaders = 0;
    std::vector<std::vector<std::shared_ptr<Spaceinvader>>> invaders;
    std::shared_ptr<TextComponent> score_text;
};

#endif