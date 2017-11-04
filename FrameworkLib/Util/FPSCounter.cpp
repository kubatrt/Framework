#include <iostream>
#include "FPSCounter.hpp"
#include "../ResourceManager/ResourceHolder.hpp"

namespace framework
{

FPSCounter::FPSCounter()
{
    text_.move(10, 10);
    text_.setOutlineColor (sf::Color::Black);
    text_.setFillColor(sf::Color::Yellow);
    text_.setOutlineThickness  (2);
    text_.setFont(ResourceHolder::get().fonts.get("arial"));
    text_.setCharacterSize(24);
}


void FPSCounter::update(sf::Time deltaTime)
{
    m_frameCount++;

    if (m_delayTimer.getElapsedTime().asSeconds() > 0.2)
    {
        m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();
        m_frameCount = 0;
        m_delayTimer.restart();
    }
}

void FPSCounter::draw(sf::RenderTarget& renderer)
{
    text_.setString("FPS: " + std::to_string((int)m_fps));
    renderer.draw(text_);
}

}