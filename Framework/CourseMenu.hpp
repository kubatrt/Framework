#pragma once

#include "../FrameworkLib/States/StateBase.hpp"
#include "../FrameworkLib/GUI/StackMenu.hpp"
#include "../FrameworkLib/BaseGame.hpp"

namespace example
{

namespace fw = framework;

class CourseMenu : public framework::StateBase
{
public:
    CourseMenu(framework::BaseGame& game);

    void handleEvent(sf::Event e) override;
    //void handleInput(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void fixedUpdate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    fw::gui::StackMenu courseMenu_;
};

}
