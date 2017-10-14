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
        void draw         (sf::RenderTarget& renderer);

    private:
        void initWidget(Widget& w);

        std::vector<std::unique_ptr<Widget>> widgets_;
        sf::RectangleShape background_;

        sf::Vector2f basePosition_;
        sf::Vector2f baseSize_;
};

template <typename T, typename... Args>
void StackMenu::addWidget(Args&&... args)
{
    widgets_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

}
}
