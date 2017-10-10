#pragma once

#include "StateBase.hpp"
#include "../GUI/StackMenu.hpp"

namespace framework
{

class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleEvent    (sf::Event e) override;
        void handleInput() override;
        void update         (sf::Time deltaTime) override;
        void fixedUpdate(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

    private:
        gui::StackMenu m_TestMenu;
};

}