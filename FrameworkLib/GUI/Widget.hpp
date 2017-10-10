#pragma once

#include <SFML/Graphics.hpp>
#include "../ResourceManager/ResourceHolder.hpp"


namespace framework
{
namespace gui
{

// warning pressure C4244
sf::Vector2f itof(sf::Vector2i vec);


class Widget
{
    public:
        virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;
        
		virtual void render(sf::RenderTarget& renderer) = 0;
        
		virtual void setPosition(const sf::Vector2f& pos) = 0;
        virtual sf::Vector2f getSize() const = 0;

    protected:
        class Text : public sf::Text
        {
            public:
                Text();
        };

        class Rectangle : public sf::RectangleShape
        {
            public:
                bool isRolledOn(const sf::RenderWindow& window) const;
                bool isClicked(sf::Event, const sf::RenderWindow& window);
        };
};

}
}