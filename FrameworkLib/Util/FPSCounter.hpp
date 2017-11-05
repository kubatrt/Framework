#pragma once

#include <SFML\Graphics.hpp>

namespace framework
{

class FPSCounter
{
    public:
        FPSCounter();

        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& renderer);

    private:
        sf::Text text_;
        sf::Font m_font;

        sf::Clock m_delayTimer;
        sf::Clock m_fpsTimer;

        float m_fps = 0;
        int m_frameCount = 0;
};

}