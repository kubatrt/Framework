#include "WritingGame.hpp"

namespace km
{

WritingGame::WritingGame(fw::GameBase& game)
    : StateBase(game)
{

}

void WritingGame::handleEvents(sf::Event e)
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

void WritingGame::update(sf::Time deltaTime)
{

}

void WritingGame::draw(sf::RenderTarget& renderer)
{

}

}
