#include "StateMenu.hpp"

#include "../../FrameworkLib/GUI/Button.hpp"
#include "../../FrameworkLib/GUI/Textbox.hpp"
#include "../Game.hpp"

#include <iostream>
#include <string>
#include <memory>


namespace framework
{

StateMenu::StateMenu(Game& game)
	: StateBase(game)
	, testMenu_({ game.getWindow().getSize().x / 2.f, 90.f })
{
    auto b = std::make_unique<gui::Button>();
    b->setText("Button 1");
    b->setFunction([]() {
        std::cout << "Button 1 clicked!\n";
    });

	auto b2 = std::make_unique<gui::Button>();
	b2->setText("Quit");
	b2->setFunction( [&]() 
	{
		game_.close();
	});

	auto b3 = std::make_unique<gui::Button>();
	b3->setText("Button 3");
	b3->setFunction([&] ()
	{
		std::cout << "Button 3 clicked!\n";
	});

    testMenu_.addWidget(std::move(b));
	testMenu_.addWidget(std::move(b2));
	testMenu_.addWidget(std::move(b3));
}

void StateMenu::handleEvent(sf::Event e)
{
    testMenu_.handleEvent(e, game_.getWindow());
}

void StateMenu::handleInput()
{

}

void StateMenu::update(sf::Time deltaTime)
{

}

void StateMenu::fixedUpdate(sf::Time deltaTime)
{

}

void StateMenu::draw(sf::RenderTarget& renderer)
{
    testMenu_.draw(renderer);
}

}