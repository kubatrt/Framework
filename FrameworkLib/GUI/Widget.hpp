#pragma once

#include <SFML/Graphics.hpp>
#include "../ResourceManager/ResourceHolder.hpp"


namespace framework
{
namespace gui
{

// warning pressure C4244
sf::Vector2f itof(sf::Vector2i vec);

struct IWidget
{;
	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderTarget& renderer) = 0;
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual sf::Vector2f getSize() const = 0;
};

class Widget : IWidget
{
    public:
        Widget();
		virtual ~Widget() = default;
		
		virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) {};
		virtual void draw(sf::RenderTarget& renderer) {};
		virtual void setPosition(const sf::Vector2f& pos) {};
        virtual sf::Vector2f getSize() const = 0;

		void select(bool selected) { isSelected_ = selected; }
		bool isSelected() const { return isSelected_; }
		void active(bool active) { isActive_ = active; }
		bool isActive() const { return isActive_; }

		static unsigned int selectionIdndexCounter;
		static unsigned int currentSelectionIndex;
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

		static const unsigned defaultCharacterSize = 20;



		unsigned int selectionIndex_;
		bool isSelected_;
		bool isActive_;
};

}
}