#pragma once
#include <SFML\Graphics.hpp>
#include "Misc.hpp"

namespace km
{

// comments cloud displayed in menu with option description
struct CommentCloud
{
    sf::Sprite cloudSprite_;
    sf::Text textUI_;
    std::string comment_;
};

}