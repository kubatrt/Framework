#include "WritingGame.hpp"

namespace km
{

WritingGame::WritingGame(fw::GameBase& game)
    : StateBase(game)
{

}

void WritingGame::handleEvents(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.popState();
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
