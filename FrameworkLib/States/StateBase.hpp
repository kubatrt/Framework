#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../IState.hpp"


namespace framework
{

class BaseGame;

class StateBase : IState
{
public:
    StateBase(BaseGame& game)
    : game_(game)
    {}
    virtual ~StateBase() = default;
    StateBase(const StateBase&) = delete;
    const StateBase& operator=(const StateBase&) = delete;


    virtual void handleEvent(sf::Event e) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void fixedUpdate(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;

protected:
    virtual void handleInput(sf::Event e) = 0; // does it have sens?

    BaseGame& game_;
};
using StateBasePtr = std::unique_ptr<StateBase> ;
using StateBaseSPtr = std::shared_ptr<StateBase>;

}
