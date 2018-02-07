#include "GalleryGame.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

GalleryGame::GalleryGame(fw::GameBase& game)
    : StateBase(game)
    , picture_(
        framework::ResourceHolder::get().textures.get("obraz_1"),
        game.getWindow().getSize().x, game.getWindow().getSize().y, 2, 2)
    //, dictionary_("data/words_01")
{
    
}

void GalleryGame::handleEvents(sf::Event e)
{
    // handle events

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.popState();
        else if (e.key.code == sf::Keyboard::F12)
            game_.toggleFullscreen();
        break;

    case sf::Event::TextEntered:
        typedLetter_ = static_cast<wchar_t>(e.text.unicode);
        textEnteredEvent();
        break;
    default:
        break;
    }
}

void GalleryGame::textEnteredEvent()
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

void GalleryGame::enterWord()
{
    std::wcout << "Entered word: " << typedWord_ << std::endl;
    picture_.typedWord(typedWord_);
    typedWord_.clear();
}

void GalleryGame::update(sf::Time deltaTime)
{
    picture_.update(deltaTime);

    if (picture_.isComplete())
    {
        game_.popState();
    }
}

void GalleryGame::draw(sf::RenderTarget& renderer)
{
    picture_.draw(renderer);
}

}
