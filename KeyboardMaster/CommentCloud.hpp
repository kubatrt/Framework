#pragma once
#include <SFML\Graphics.hpp>
#include "Misc.hpp"

namespace km
{

// comments cloud displayed in menu with option description
struct CommentCloud : km::Rectangle
{
    sf::Sprite cloud;
    sf::Text    text;
    std::string comment;
};

}