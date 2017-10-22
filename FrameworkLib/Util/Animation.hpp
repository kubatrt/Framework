#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
    public:
        struct Frame
        {
            Frame(const sf::IntRect& bnds, sf::Time dly)
                : bounds(bnds)
                , delay(dly) {}

            sf::IntRect bounds;
            sf::Time delay;
        };

        Animation(unsigned frameSize);

        void addFrame(unsigned index, sf::Time delay);
        const sf::IntRect& getFrame();

    private:
        sf::Clock timer_;

        std::vector<Frame> frames_;

        unsigned framePointer_ = 0;
        const unsigned FRAME_SIZE;

};
