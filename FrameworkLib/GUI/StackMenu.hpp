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


class StackMenu : public framework::NonCopyable
{
    public:
        StackMenu(const sf::Vector2f& position);
        
		StackMenu(StackMenu&& other);
        StackMenu& operator =(StackMenu&& other);

        ~StackMenu() = default;

        void addWidget(std::unique_ptr<Widget>);

        void handleEvent(sf::Event e, const sf::RenderWindow& window);
        void draw(sf::RenderTarget& renderer);

    protected:

        void initWidget(Widget& w);
		void alignSize();

        std::vector<std::unique_ptr<Widget>> widgets_;
        sf::RectangleShape background_;

        sf::Vector2f basePosition_;
        sf::Vector2f baseSize_;
};

}
}
