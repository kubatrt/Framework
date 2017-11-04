#pragma once

#include <SFML/Graphics.hpp>


namespace framework
{

struct IEntity
{
    virtual void draw(sf::RenderTarget&) = 0;   // Drawable
    virtual void update(sf::Time) = 0;          // Updateable
};

}