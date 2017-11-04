#pragma once

#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "States\StateBase.hpp"
#include "IApplication.hpp"

namespace framework
{

class GameBase : IApplication
{
public:
    GameBase(sf::Vector2u windowSize, std::string windowTitle)
        : window_(sf::VideoMode(windowSize.x, windowSize.y), windowTitle)
        , windowWidth_(windowSize.x)
        , windowHeight_(windowSize.y)
        , windowTitle_(windowTitle)
        , popState_(false)
        , isFullscreen_(false)
    {
    }
    virtual ~GameBase() = default;

    GameBase(const GameBase&) = delete;
    const GameBase& operator=(const GameBase&) = delete;
    GameBase(GameBase&&) = delete;
    GameBase&& operator=(GameBase&&) = delete;

    //-------------------------------------------------------------------------
    // This interface should not be able to call within a state
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;

    // this hould be defined elsewhere, outside this class. I can call it in some state public method run()
    virtual int run()
    {
        sf::Clock timer;
        auto lastTime = sf::Time::Zero;

        while (window_.isOpen())
        {
            auto time = timer.getElapsedTime();
            auto elapsed = time - lastTime;
            lastTime = time;

            update(elapsed);
            draw(window_);

            handleEvents();
            tryPop();
        }
        return 0;
    }

    virtual void handleEvents() = 0;
    //-------------------------------------------------------------------------

    // State management
    template<typename T, typename... Args>
    void pushState(Args&&... args)
    {
        states_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    };
    void popState()
    {
        popState_ = true;
    };

    // Access in States
    const sf::RenderWindow& getWindow() const { return window_; };
    void close() { window_.close(); };
    void create()
    {
        auto style = isFullscreen_ ? sf::Style::Fullscreen : sf::Style::Default;
        window_.create({windowWidth_, windowHeight_}, windowTitle_, style);
    }
    void toggleFullscreen()
    {
        isFullscreen_ = !isFullscreen_;
        close();
        create();
    }

protected:
    StateBase& getCurrentState()
    {
        // Atleast one state required - or throw exception? or can be null? use pointer instead!
        assert(states_.size()); // give up with assertions... ~Mayers
        return *states_.back(); // return reference
    };

    void tryPop()
    {
        if (popState_)
        {
            states_.pop_back();
        }
        popState_ = false;
    };

    sf::RenderWindow window_;

private:
    std::vector<std::unique_ptr<StateBase>> states_;
    bool popState_;
    bool isFullscreen_;
    std::string windowTitle_;
    sf::Uint32 windowWidth_;
    sf::Uint32 windowHeight_;
};


}   // framework
