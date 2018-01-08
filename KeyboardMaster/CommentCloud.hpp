#pragma once
#include <SFML\Graphics.hpp>
#include "Misc.hpp"

namespace km
{

// comments cloud displayed in menu with option description
struct CommentCloud : km::Rectangle
{
    sf::Sprite cloud_;
    sf::Text    text_;
    std::string comment_;
};

}