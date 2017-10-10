#pragma once

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Widget.hpp"

namespace framework
{
namespace gui
{

// TODO
class Panel
{
    public:
		Panel(const sf::RenderWindow& window);

        template <typename T, typename... Args>
        void addWidget(Args&&... args);


        void addWidget(std::unique_ptr<Widget>);

        void handleEvent   (sf::Event e, const sf::RenderWindow& window);
        void render         (sf::RenderTarget& renderer);

    private:
        void initWidget(Widget& w);

        std::vector<std::unique_ptr<Widget>> m_widgets;
        sf::RectangleShape m_background;

        sf::Vector2f m_basePosition;
        sf::Vector2f m_baseSize;
};

template <typename T, typename... Args>
void StackMenu::addWidget(Args&&... args)
{
    m_widgets.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

}
}
