#ifndef INVADERS_H
#define INVADERS_H
#include <Spaceinvader.h>
#include <Color.h>
#include "MultipartRectangleTexture.h"

class InvadersComponent : public Component
{
public:
    static std::unique_ptr<InvadersComponent> createInstance(std::shared_ptr<Session> session, int x, int y, int numRows, int numCols, int invaderWidth, int invaderHeight, int invaderSpacing)
    {
        return std::unique_ptr<InvadersComponent>(new InvadersComponent(session, x, y, numRows, numCols, invaderWidth, invaderHeight, invaderSpacing));
    }

    void createInvaders()
    {
        invaders.resize(numCols, std::vector<std::shared_ptr<Spaceinvader>>(numRows));

        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
                int x = col * (invaderWidth + invaderSpacing);
                int y = row * (invaderHeight + invaderSpacing);
                auto invader = Spaceinvader::createInstance(session, x + get_rect().x, y + get_rect().y, invaderWidth, invaderHeight, 100, "images/alive.png", "images/dead.png", 29 + row);
                auto invader_ref = session->add_component(std::move(invader));
                invaders[col][row] = std::dynamic_pointer_cast<Spaceinvader>(invader_ref);
            }
        }
    }

    bool safe_to_shoot(int col, int row)
    {
        // Since rows move at different speeds and in different directions
        // we need to check if there effectively is a row in front of us
        // if there is, we can't shoot
        if (row == numRows - 1)
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
        int laser_x = invader->get_rect().x + (invader->get_rect().w / 2);
        int laser_y = invader->get_rect().y + invader->get_rect().h;

        // check all components in front of us to see if they are in the way or are going to be in the way before
        // the laser is clear of the invaders rect
        // we assume that all entities below us are moving +-2 pixels per tick in x-direction
        int ticks_to_clear = (get_rect().y + get_rect().h - laser_y) / laser_dy;
        int ticks_to_clear_x = ticks_to_clear * 2;
        int ticks_to_clear_y = ticks_to_clear * laser_dy;
        int left_x_bound = laser_x - ticks_to_clear_x;
        int right_x_bound = laser_x + ticks_to_clear_x;
        int top_y_bound = laser_y;
        int bottom_y_bound = get_rect().y + get_rect().h;
        // Draw multipart component with the dimensions above
        std::unique_ptr<MultipartComponent> multipart = MultipartComponent::createInstance(session, left_x_bound, top_y_bound, right_x_bound - left_x_bound, bottom_y_bound - top_y_bound, false);
        auto multipartRectangle = MultipartRectangleTexture::createInstance(session, right_x_bound - left_x_bound, bottom_y_bound - top_y_bound, Color(255, 0, 0, 128));
        multipart->addTexture(multipartRectangle);
        session->add_component(std::move(multipart));

        // check if there is a component in the way of all components below us
        for (int r = row + 1; r < numRows; r++)
        {
            for (int c = 0; c < numCols; c++)
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
                if (other_invader->get_rect().x + other_invader->get_rect().w < left_x_bound)
                {
                    continue;
                }
                if (other_invader->get_rect().x > right_x_bound)
                {
                    continue;
                }
                if (other_invader->get_rect().y + other_invader->get_rect().h < top_y_bound)
                {
                    continue;
                }
                if (other_invader->get_rect().y > bottom_y_bound)
                {
                    continue;
                }
                std::cout << "Can't shoot, invader " << col << "," << row << " is in the way!" << std::endl;
                return false;
            }
        }
        return true;
    }

    bool shootBottomOfColumn(int col)
    {
        for (int row = numRows - 1; row >= 0; row--)
        {
            if (invaders[col][row].get() != nullptr)
            {
                auto invader = invaders[col][row];
                if (invader->is_dead())
                {
                    invaders[col][row] = nullptr;
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

    void shootRandomInvader()
    {
        std::vector<int> columns;
        for (int col = 0; col < numCols; col++)
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
            if (shootBottomOfColumn(col))
            {
                return;
            }
        }
    }

    void shootBottomInvaders()
    {
        for (int col = 0; col < numCols; col++)
        {
            if (!invaders[col].empty())
            {
                for (int row = numRows - 1; row >= 0; row--)
                {
                    if (invaders[col][row] != nullptr)
                    {
                        auto invader = invaders[col][row];
                        if (invader->is_dead())
                        {
                            invaders[col][row] = nullptr;
                            continue;
                        }
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
        if (!created)
        {
            createInvaders();
            created = true;
        }
        if (tick_count % 100 == 0)
        {
            shootRandomInvader();
        }
    }

    void render() const override
    {
    }

protected:
    InvadersComponent(std::shared_ptr<Session> session, int x, int y, int numRows, int numCols, int invaderWidth, int invaderHeight, int invaderSpacing)
        : Component(
              session, x, y, [&]()
              { return numCols * (invaderWidth + invaderSpacing) - invaderSpacing; }(),
              [&]()
              { return numRows * (invaderHeight + invaderSpacing) - invaderSpacing; }(),
              false),
          numRows(numRows), numCols(numCols),
          invaderWidth(invaderWidth), invaderHeight(invaderHeight), invaderSpacing(invaderSpacing)
    {
    }

private:
    bool created = false;
    int tick_count = 0;
    int numRows;
    int numCols;
    int invaderWidth;
    int invaderHeight;
    int invaderSpacing;
    std::vector<std::vector<std::shared_ptr<Spaceinvader>>> invaders;
};

#endif