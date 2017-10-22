#pragma once

#include "../FrameworkLib/States/StateBase.hpp"
#include "../FrameworkLib/GUI/StackMenu.hpp"

namespace framework
{

class MainMenu : public StateBase
{
public:
    MainMenu(Game& game);

    void handleEvent(sf::Event e) override;
    void handleInput() override;
    void update(sf::Time deltaTime) override;
    void fixedUpdate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    gui::StackMenu testMenu_;
};

}