#pragma once

#include "IWidget.hpp"
#include "../ResourceManager/ResourceHolder.hpp"


namespace framework
{
namespace gui
{

// warning pressure C4244
sf::Vector2f itof(sf::Vector2i vec);

class Widget : IWidget
{
public:
    Widget();
    virtual ~Widget() = default;

    virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) {};
    virtual void draw(sf::RenderTarget& renderer) {};
    virtual void setPosition(const sf::Vector2f& pos) {};
    virtual sf::Vector2f getSize() const = 0;

    // Selection
    void setSelection(bool selected) { isSelected_ = selected; }
    bool isSelected() const { return isSelected_; }

    void setActive(bool active) { isActive_ = active; }
    bool isActive() const { return isActive_; }

    static unsigned int selectionIdndexCounter;
    static unsigned int currentSelectionIndex;

protected:
    static const unsigned defaultCharacterSize = 20;

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

    unsigned int selectionIndex_;
    bool isSelected_;
    bool isActive_;
};

}
}