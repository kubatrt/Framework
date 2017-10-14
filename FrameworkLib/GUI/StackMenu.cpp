#include "StackMenu.hpp"

#include "../ResourceManager/ResourceHolder.hpp"

namespace framework
{

namespace gui
{
/*
StackMenu::StackMenu(const sf::RenderWindow& window) // ACCESSWINDOW HERE?
	: basePosition_ (window.getSize().x / 2.f, StackMenu::baseY)
	, baseSize_(300.f, 20.f)
{
    m_background.setFillColor({100, 100, 100, 128});
    m_background.setSize(baseSize_);
    m_background.setPosition(basePosition_.x - baseSize_.x / 2.f, StackMenu::baseY - 30.f);
}*/

StackMenu::StackMenu(const sf::Vector2f& position)
	: basePosition_(position)
	, baseSize_(StackMenu::defaultHeight, StackMenu::defaultWidth)
{
    background_.setFillColor({100, 100, 100, 128});
    background_.setSize(baseSize_);
	background_.setPosition(basePosition_.x - baseSize_.x / 2.f, StackMenu::defaultY - StackMenu::defaultWidth);
}

StackMenu::StackMenu(StackMenu&& other)
	: widgets_(std::move(other.widgets_))
	, background_(std::move(other.background_))
	, basePosition_(other.basePosition_)
	, baseSize_(other.baseSize_)
{
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    widgets_  = std::move(other.widgets_);
    background_ = std::move(other.background_);
    basePosition_ = other.basePosition_;
    baseSize_  = other.baseSize_;
    return *this;
}

void StackMenu::addWidget(std::unique_ptr<Widget> w)
{
    initWidget(*w);
    widgets_.push_back(std::move(w));
}

void StackMenu::initWidget(Widget& widget)
{
    widget.setPosition({basePosition_.x - widget.getSize().x / 2,
                       basePosition_.y});

    basePosition_.y += widget.getSize().y + 25.f;
    baseSize_.y += widget.getSize().y + 25.f;
    background_.setSize(baseSize_);
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : widgets_)
    {
        widget->handleEvent(e, window);
    }
}

void StackMenu::draw(sf::RenderTarget& renderer)
{
    renderer.draw(background_);
    for (auto& widget : widgets_)
    {
        widget->draw(renderer);
    }
}

}
}
