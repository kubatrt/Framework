#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace framework
{

// TODO
class Animation
{
    public:
        struct Frame
        {
            Frame(const sf::IntRect& bnds, sf::Time dlay)
                : bounds(bnds)
                , delay(dlay) {}

            sf::IntRect bounds;
            sf::Time delay;
        };

        Animation(unsigned frameSize);

        void addFrame(unsigned index, sf::Time delay);
        const sf::IntRect& getFrame();

    private:
        sf::Clock timer_;
        std::vector<Frame> frames_;
        unsigned currentFrame_ = 0;
        const unsigned FRAME_SIZE;
};

}