#include "StatePlaying.hpp"

#include "../GUI/Button.hpp"
#include "../GUI/Textbox.hpp"
#include "../Game.hpp"

#include <iostream>
#include <string>
#include <memory>


namespace framework
{

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, testMenu_({ game.getWindow().getSize().x / 2.f, 90.f })
{
    auto b = std::make_unique<gui::Button>();
    b->setText("Button 1");
    b->setFunction([]() {
        std::cout << "Button 1 clicked!" << '\n';
    });

	auto b2 = std::make_unique<gui::Button>();
	b2->setText("Quit");
	b2->setFunction( [&]() 
	{
		game_.close();
	});
	b2->setPosition({100.f, 200.f});

    testMenu_.addWidget(std::move(b));
	testMenu_.addWidget(std::move(b2));
}

void StatePlaying::handleEvent(sf::Event e)
{
    testMenu_.handleEvent(e, game_.getWindow());
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(sf::Time deltaTime)
{

}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::draw(sf::RenderTarget& renderer)
{
    testMenu_.draw(renderer);
}

}