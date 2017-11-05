#include "KeyboardMaster.hpp"
#include "MainMenu.hpp"
#include "CourseGame.hpp"
#include "WordsGame.hpp"
#include "GalleryGame.hpp"
#include "../FrameworkLib/ResourceManager/ResourceManager.hpp"

namespace km
{

KeyboardMaster::KeyboardMaster()
    : fw::GameBase({ 1280, 720 }, "Catch game")
{
    window_.setFramerateLimit(60);  // instead of separate fixedUpdate
    pushState<MainMenu>(*this);
    //pushState<CourseMenu>(*this);

    //fw::ResourceManager<sf::Font>::get("arial");
}

void KeyboardMaster::update(sf::Time deltaTime)
{
    getCurrentState().update(deltaTime);
    fpsCounter_.update(deltaTime);
}

void KeyboardMaster::draw(sf::RenderTarget& renderer)
{
    window_.clear();

    getCurrentState().draw(window_);
    fpsCounter_.draw(window_);

    window_.display();
}

void KeyboardMaster::handleEvents()
{
    sf::Event e;

    while (window_.pollEvent(e))
    {
        getCurrentState().handleEvents(e);

        switch (e.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        default:
            break;
        }
    }
}

}
