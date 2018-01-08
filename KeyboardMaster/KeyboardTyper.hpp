#pragma once

#include "Misc.hpp"

namespace km
{

// TODO
class KeyboardTyper
{
public:
    KeyboardTyper() = default;
    ~KeyboardTyper() = default;

    float getKPM() { return keysPerMinute_; }
    float getKPW() { return keysPerWord_; }

    void start() {};
    void pause() {};
    void stop() {};

private:
    uint keysTyped_;
    uint wordsTyped_;
    float keysPerMinute_;
    float keysPerWord_;
};

} // km