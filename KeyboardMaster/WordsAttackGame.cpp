#include "WordsAttackGame.hpp"

namespace km
{

WordsAttackGame::WordsAttackGame(fw::GameBase& game)
    : StateBase(game)
{

}

void WordsAttackGame::handleEvents(sf::Event e)
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

void WordsAttackGame::update(sf::Time deltaTime)
{

}

void WordsAttackGame::draw(sf::RenderTarget& renderer)
{

}

}
