#pragma once

#include <SFML/Graphics.hpp>


namespace framework
{

struct IEntity
{
	virtual void draw(sf::RenderTarget&) = 0;
	virtual void update(sf::Time) = 0;
};

}