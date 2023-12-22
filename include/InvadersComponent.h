#ifndef INVADERS_H
#define INVADERS_H
#include <Spaceinvader.h>
#include <TextComponent.h>

class InvadersComponent : public Component
{
public:
    static std::unique_ptr<InvadersComponent> createInstance(std::shared_ptr<Session> session, int x, int y, int numRows, int numCols, int invaderWidth, int invaderHeight, int invaderSpacing, std::shared_ptr<TextComponent> score_text) {
        return std::unique_ptr<InvadersComponent>(new InvadersComponent(session, x, y, numRows, numCols, invaderWidth, invaderHeight, invaderSpacing, score_text));
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
                auto invader = Spaceinvader::createInstance(session, x, y, invaderWidth, invaderHeight, 100, "images/alive.png", "images/dead.png", 1);
                auto invader_ref = session->add_component(std::move(invader));
                invaders[col][row] = std::dynamic_pointer_cast<Spaceinvader>(invader_ref);
                total_invaders++;
                alive_invaders++;
            }
        }
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
                            alive_invaders--;
                            invaders[col][row] = nullptr;
                        }
                    }
                }
            }
        }
        if (tick_count % 100 == 0)
        {
            shootRandomInvader();
        }
        score_text->setText("Score: " + std::to_string(total_invaders - alive_invaders));
    }

    void render() const override
    {
    }
protected:
    InvadersComponent(std::shared_ptr<Session> session, int x, int y, int numRows, int numCols, int invaderWidth, int invaderHeight, int invaderSpacing, std::shared_ptr<TextComponent> score_text)
        : Component(
              session, x, y, [&]()
              { return numCols * (invaderWidth + invaderSpacing) - invaderSpacing; }(),
              [&]()
              { return numRows * (invaderHeight + invaderSpacing) - invaderSpacing; }(),
              false),
          numRows(numRows), numCols(numCols),
          invaderWidth(invaderWidth), invaderHeight(invaderHeight), invaderSpacing(invaderSpacing), score_text(score_text)
    {
        createInvaders();
    }
private:
    int tick_count = 0;
    int numRows;
    int numCols;
    int invaderWidth;
    int invaderHeight;
    int invaderSpacing;
    int total_invaders = 0;
    int alive_invaders = 0;
    std::vector<std::vector<std::shared_ptr<Spaceinvader>>> invaders;
    std::shared_ptr<TextComponent> score_text;
};

#endif