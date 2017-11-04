#pragma once

#include "../FrameworkLib/States/StateBase.hpp"
#include "../FrameworkLib/GUI/StackMenu.hpp"
#include "../FrameworkLib/GameBase.hpp"

namespace example
{

namespace fw = framework;

class CourseMenu : public framework::StateBase
{
public:
    CourseMenu(framework::GameBase& game);

    void handleEvent(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    fw::gui::StackMenu courseMenu_;
};

}
