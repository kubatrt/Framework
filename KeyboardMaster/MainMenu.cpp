#include <iostream>
#include <string>
#include <memory>

#include "MainMenu.hpp"
#include "CourseGame.hpp"
#include "GalleryGame.hpp"
#include "WordsAttackGame.hpp"
#include "WritingGame.hpp"
#include "../FrameworkLib/GUI/Button.hpp"
#include "../FrameworkLib/GUI/Textbox.hpp"


namespace km
{

MainMenu::MainMenu(fw::GameBase& game)
    : StateBase(game)
    , menu_({ game.getWindow().getSize().x / 2.f, 90.f })
{
    auto b = std::make_unique<fw::gui::Button>();
    b->setText("Go to course");
    b->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_);
    });

    auto b2 = std::make_unique<fw::gui::Button>();
    b2->setText("Words attack!");
    b2->setFunction([&] ()
    {
        game_.pushState<WordsAttackGame>(game_);
    });

    auto b3 = std::make_unique<fw::gui::Button>();
    b3->setText("Gallery");
    b3->setFunction([&] ()
    {
        game_.pushState<GalleryGame>(game_);
    });

    auto b4 = std::make_unique<fw::gui::Button>();
    b4->setText("Writing");
    b4->setFunction([&] ()
    {
        game_.pushState<WritingGame>(game_);
    });

    auto bquit = std::make_unique<fw::gui::Button>();
    bquit->setText("Quit");
    bquit->setFunction([&] ()
    {
        game_.close();
    });

    menu_.addWidget(std::move(b));
    menu_.addWidget(std::move(b2));
    menu_.addWidget(std::move(b3));
    menu_.addWidget(std::move(b4));
    menu_.addWidget(std::move(bquit));
}

void MainMenu::handleEvents(sf::Event e)
{
    menu_.handleEvent(e, game_.getWindow());

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

void MainMenu::update(sf::Time deltaTime)
{

}

void MainMenu::draw(sf::RenderTarget& renderer)
{
    menu_.draw(renderer);
}

}
