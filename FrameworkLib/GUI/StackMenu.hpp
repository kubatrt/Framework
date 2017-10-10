#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Widget.hpp"
#include "../Util/NonCopyable.hpp"

namespace framework
{

namespace gui
{

// TODO
class StackMenu : public framework::NonCopyable
{
    public:
        StackMenu(const sf::RenderWindow& window);
        StackMenu(const sf::Vector2f& position);
        
		StackMenu(StackMenu&& other);
        StackMenu& operator =(StackMenu&& other);

        ~StackMenu() = default;

        void addWidget(std::unique_ptr<Widget>);

        void handleEvent(sf::Event e, const sf::RenderWindow& window);
        void render(sf::RenderTarget& renderer);

    private:
        void initWidget(Widget& w);

        std::vector<std::unique_ptr<Widget>> m_widgets;
        sf::RectangleShape m_background;

        sf::Vector2f m_basePosition;
        sf::Vector2f m_baseSize;
};

}
}
