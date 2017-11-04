#pragma once

#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "States\StateBase.hpp"

namespace framework
{

struct IGame
{
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
    virtual int run() = 0;
};


class BaseGame : IGame
{
public:
    BaseGame(sf::Vector2u windowSize, std::string windowTitle)
        : window_(sf::VideoMode(windowSize.x, windowSize.y), windowTitle)
        , windowWidth_(windowSize.x)
        , windowHeight_(windowSize.y)
        , windowTitle_(windowTitle)
        , popState_(false)
        , isFullscreen_(false)
    {
    }
    virtual ~BaseGame() = default;

    BaseGame(const BaseGame&) = delete;
    const BaseGame& operator=(const BaseGame&) = delete;
    BaseGame(BaseGame&&) = delete;
    BaseGame&& operator=(BaseGame&&) = delete;


    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
    virtual int run() = 0;

    template<typename T, typename... Args>
    void pushState(Args&&... args)
    {
        states_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    };
    void popState()
    {
        popState_ = true;
    };

    // access in States
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
        // minimum one state required
        // if want return reference...
        // or throw exception?
        assert(states_.size()); // poddaj si� z asercjami! :) ~Mayers
        // can be null? use pointer instead
        return *states_.back();
    };

    void handleEvents()
    {
        sf::Event e;

        while (window_.pollEvent(e))
        {
            getCurrentState().handleEvent(e);   // implicite

            switch (e.type)
            {
            case sf::Event::Closed:
                window_.close();
                break;
            default:
                // debug
                break;
            }
        }
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
