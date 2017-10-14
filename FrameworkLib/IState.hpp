#pragma once

#include <SFML\Graphics.hpp>

namespace framework
{

struct IState
{
	virtual void handleEvent(sf::Event e) = 0;
	virtual void handleInput() = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void fixedUpdate(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderTarget& renderer) = 0;

};
}