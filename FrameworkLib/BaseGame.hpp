#pragma once

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
    BaseGame(sf::RenderWindow& window)
        : window_(window)
        , popState_(false)
    {
    }
    virtual ~BaseGame() = default;
    BaseGame(const BaseGame&) = delete;
    const BaseGame& operator=(const BaseGame&) = delete;


    void update(sf::Time deltaTime) override {};
    void draw(sf::RenderTarget& renderer) override {};
    int run() override { return 0; };

    template<typename T, typename... Args>
    void pushState(Args&&... args)
    {
        states_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    };
    void popState()
    {
        states_.pop_back();
    };

    const sf::RenderWindow& getWindow() const { return window_; };
    void close() { window_.close(); };

protected:
    sf::RenderWindow& window_;
    std::vector<std::unique_ptr<StateBase>> states_;
    bool popState_;

    StateBase& getCurrentState()
    {
        // minimum one state required
        // if want return reference...
        assert(states_.size()); // poddaj siê z asercjami! :) ~Mayers
        return *states_.back();
    };

    void handleEvents()
    {
        sf::Event e;

        while (window_.pollEvent(e))
        {
            getCurrentState().handleEvent(e);

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
};


}   // framework
