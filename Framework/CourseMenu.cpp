#include <iostream>
#include <string>
#include <memory>
#include "CourseMenu.hpp"
#include "Game.hpp"
#include "../FrameworkLib/GUI/Button.hpp"
#include "../FrameworkLib/GUI/Textbox.hpp"
#include "../FrameworkLib/Util/Files.hpp"
#include "../FrameworkLib/Utilities.hpp"


namespace framework
{

CourseMenu::CourseMenu(Game& game)
    : StateBase(game)
    , courseMenu_({ game.getWindow().getSize().x / 2.f, 90.f })
{
    std::string coursesText = framework::loadTextFromFile("data/courses.txt");
    std::vector<std::string> coursesLines = framework::getLinesFromText(coursesText);

    for(const auto line : coursesLines)
    {
        auto button = std::make_unique<gui::Button>();
        button->setText(line);
        button->setFunction([&] ()
        {

        });
        courseMenu_.addWidget(std::move(button));
    }

    auto bback = std::make_unique<gui::Button>();
    bback->setText("Back");
    bback->setFunction([&]()
    {
        game_.popState();
    });

    courseMenu_.addWidget(std::move(bback));
}

void CourseMenu::handleEvent(sf::Event e)
{
    courseMenu_.handleEvent(e, game_.getWindow());
}

void CourseMenu::handleInput()
{

}

void CourseMenu::update(sf::Time deltaTime)
{

}

void CourseMenu::fixedUpdate(sf::Time deltaTime)
{

}

void CourseMenu::draw(sf::RenderTarget& renderer)
{
    courseMenu_.draw(renderer);
}

}