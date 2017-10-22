#pragma once


namespace framework
{

struct IGameState
{
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onPlay() = 0;
    virtual void onPause() = 0;
    virtual void onStop() = 0;
};

} // framework