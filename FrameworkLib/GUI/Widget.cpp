#include "Widget.hpp"

namespace framework
{
namespace gui 
{

sf::Vector2f itof(sf::Vector2i vec)
{
	return sf::Vector2f(static_cast<float>(vec.x), static_cast<float>(vec.y));
}

// Text
Widget::Text::Text()
{
    setCharacterSize (20);
    setOutlineColor  (sf::Color::Black);
    setFillColor     (sf::Color::White);
    setFont          (ResourceHolder::get().fonts.get("arial"));
}

//Rectangle
bool Widget::Rectangle::isRolledOn(const sf::RenderWindow& window) const
{
    auto pos = sf::Mouse::getPosition((window));
    return getGlobalBounds().contains(itof(pos));
}

bool Widget::Rectangle::isClicked  (sf::Event e, const sf::RenderWindow& window)
{
    if(isRolledOn(window))
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            return e.mouseButton.button == sf::Mouse::Left;
        }
    }
    return false;
}

}
}