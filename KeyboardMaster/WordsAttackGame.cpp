#include "WordsAttackGame.hpp"
#include <memory>
#include "../FrameworkLib/Util/Observer.hpp"
#include "../FrameworkLib/Util/Random.hpp"

namespace km
{

WordsAttackGame::WordsAttackGame(fw::GameBase& game)
    : StateBase(game)
    , dictionary_("D:/Workspace/Projects/Framework/Debug/data/words_01")
    , horizontalLine(sf::Vector2f(1024, 5))
{
    clock_.restart();

    horizontalLine.setPosition(sf::Vector2f{ 0, (float)game.getWindow().getSize().x });

    spawnWordBlock();
}

void WordsAttackGame::spawnWordBlock()
{
    if(wordBlocks_.size() >= maxWordsInGame)
        return;

    int wordLength = fw::RandomMachine::getRange(dictionary_.getShortestWord(), dictionary_.getLongestWord());
    std::wstring word = dictionary_.getRandomWord(wordLength);
    sf::Vector2f velocity(0,1.f);
    int spawnHorizontalPos = game_.getWindow().getSize().x / 2;
    wordBlocks_.push_back( std::make_shared<WordBlock>(spawnHorizontalPos, word, velocity));
}

void WordsAttackGame::handleEvents(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.close();
        else if (e.key.code == sf::Keyboard::F12)
            game_.toggleFullscreen();
        break;

    case sf::Event::TextEntered:
        typedLetter_ = static_cast<wchar_t>(e.text.unicode);
        textEntered();
        break;
    default:
        break;
    }
}

void WordsAttackGame::textEntered()
{
    if (static_cast<int>(typedLetter_) == KeyCode::Enter)
    {
        enterWord();
    }
    else
    {
        typedWord_ += typedLetter_;
    }
}

void WordsAttackGame::enterWord()
{

}

void WordsAttackGame::destroyWord()
{

}


void WordsAttackGame::update(sf::Time deltaTime)
{
    for (auto &wb : wordBlocks_)
    {
        wb->update(deltaTime);
    }
}

void WordsAttackGame::draw(sf::RenderTarget& renderer)
{
    for (auto &wb : wordBlocks_)
    {
        wb->draw(renderer);
    }
}

}
