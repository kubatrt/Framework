#include "Animation.hpp"


Animation::Animation(unsigned frameSize)
    :   FRAME_SIZE  (frameSize)
{ }

void Animation::addFrame(unsigned index, sf::Time delay)
{
    sf::IntRect bounds;
    bounds.top = 0;
    bounds.height = FRAME_SIZE;
    bounds.width  = FRAME_SIZE;
    bounds.left   = index * FRAME_SIZE;

    frames_.emplace_back(bounds, delay);
}


const sf::IntRect& Animation::getFrame()
{
    if (timer_.getElapsedTime() >= frames_[framePointer_].delay)
    {
        timer_.restart();
        framePointer_++;
        if (framePointer_ == frames_.size())
            framePointer_ = 0;
    }

    return frames_[framePointer_].bounds;
}
