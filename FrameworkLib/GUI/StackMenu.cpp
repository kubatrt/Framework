#include "StackMenu.hpp"

#include "../ResourceManager/ResourceHolder.hpp"

constexpr float BASE_Y = 95.f;

namespace framework
{

namespace gui
{

StackMenu::StackMenu(const sf::RenderWindow& window)
:   m_basePosition  (window.getSize().x / 2.f, BASE_Y)
,   m_baseSize      (300.f, 20.f)
{
    m_background.setFillColor({100, 100, 100, 128});
    m_background.setSize(m_baseSize);
    m_background.setPosition(m_basePosition.x - m_baseSize.x / 2.f, BASE_Y - 30.f);
}

StackMenu::StackMenu(const sf::Vector2f& position)
:   m_basePosition  (position)
,   m_baseSize      (300.f, 20.f)
{
    m_background.setFillColor({100, 100, 100, 128});
    m_background.setSize(m_baseSize);
    m_background.setPosition(position);
}

StackMenu::StackMenu(StackMenu&& other)
	:   m_widgets       (std::move(other.m_widgets))
	,   m_background    (std::move(other.m_background))
	,   m_basePosition  (other.m_basePosition)
	,   m_baseSize      (other.m_baseSize)
{
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    m_widgets       =   std::move(other.m_widgets);
    m_background    =   std::move(other.m_background);
    m_basePosition  =   other.m_basePosition;
    m_baseSize      =   other.m_baseSize;

    return *this;
}

void StackMenu::addWidget(std::unique_ptr<Widget> w)
{
    initWidget(*w);
    m_widgets.push_back(std::move(w));
}

void StackMenu::initWidget(Widget& widget)
{
    widget.setPosition({m_basePosition.x - widget.getSize().x / 2,
                       m_basePosition.y});

    m_basePosition.y    += widget.getSize().y + 25.f;
    m_baseSize.y        += widget.getSize().y + 25.f;
    m_background.setSize(m_baseSize);
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : m_widgets)
    {
        widget->handleEvent(e, window);
    }
}

void StackMenu::render(sf::RenderTarget& renderer)
{
    renderer.draw(m_background);
    for (auto& widget : m_widgets)
    {
        widget->render(renderer);
    }
}

}
}
