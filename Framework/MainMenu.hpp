#pragma once

#include "../FrameworkLib/BaseGame.hpp"
#include "../FrameworkLib/States/StateBase.hpp"
#include "../FrameworkLib/GUI/StackMenu.hpp"

namespace example
{

namespace fw = framework;

class MainMenu : public fw::StateBase
{
public:
    MainMenu(fw::BaseGame& game);

    void handleEvent(sf::Event e) override;
    void handleInput(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void fixedUpdate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    fw::gui::StackMenu testMenu_;
};

}
