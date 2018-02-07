#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "Misc.hpp"

namespace km
{

class VirtualKeyboard : IGameComponent
{
public:
    VirtualKeyboard(sf::Vector2u windowSize);
    ~VirtualKeyboard() = default;

    VirtualKeyboard(const VirtualKeyboard&) = delete;
    VirtualKeyboard& operator= (const VirtualKeyboard&) = delete;

    void highlightLetter(int letterCode);

    sf::Sprite  layoutSprite_;
    sf::Sprite  maskSprite_;

    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    // <keyCode, Position> positions in relation to layout sprite
    std::map<int, sf::Vector2f> maskPositions;
};

}   // km