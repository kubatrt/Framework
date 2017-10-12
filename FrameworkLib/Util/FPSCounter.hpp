#pragma once

#include <SFML\Graphics.hpp>
#include "..\IEntity.hpp"

namespace framework
{

class FPSCounter : IEntity
{
    public:
        FPSCounter();

        void update(sf::Time) override;
        void draw(sf::RenderTarget& renderer) override;

    private:
        sf::Text m_text;
        sf::Font m_font;

        sf::Clock m_delayTimer;
        sf::Clock m_fpsTimer;

        float m_fps = 0;
        int m_frameCount = 0;
};

}