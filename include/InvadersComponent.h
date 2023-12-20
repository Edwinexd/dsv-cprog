#ifndef INVADERS_H
#define INVADERS_H
#include <Spaceinvader.h>

class InvadersComponent : public Component
{
public:
    static std::unique_ptr<InvadersComponent> createInstance(std::shared_ptr<Session> session, int x, int y, int numRows, int numCols, int invaderWidth, int invaderHeight, int invaderSpacing) {
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
                auto invader = Spaceinvader::createInstance(session, x, y, invaderWidth, invaderHeight, 100, "images/alive.png", "images/dead.png", 29);
                auto invader_ref = session->add_component(std::move(invader));
                invaders[col][row] = std::dynamic_pointer_cast<Spaceinvader>(invader_ref);
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
            shootBottomInvaders();
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