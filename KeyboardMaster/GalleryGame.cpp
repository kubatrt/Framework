#include "GalleryGame.hpp"

namespace km
{

GalleryGame::GalleryGame(fw::GameBase& game)
    : StateBase(game)
{

}

void GalleryGame::handleEvents(sf::Event e)
{
    // handle events

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.close();
        else if (e.key.code == sf::Keyboard::F12)
            game_.toggleFullscreen();
        break;
    default:
        break;
    }
}

void GalleryGame::update(sf::Time deltaTime)
{

}

void GalleryGame::draw(sf::RenderTarget& renderer)
{

}

}
