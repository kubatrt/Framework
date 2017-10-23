#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "../Util/NonCopyable.hpp"
#include "../IState.hpp"


namespace framework
{

class Game;

class StateBase : public NonCopyable, IState
{
public:
    StateBase(Game& game)
    : game_(game)
    {}
    virtual ~StateBase() = default;
    StateBase(const StateBase&) = delete;
    const StateBase& operator=(const StateBase&) = delete;


    virtual void handleEvent(sf::Event e) = 0;
    virtual void handleInput() = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void fixedUpdate(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;

protected:
    Game& game_;
};
using StateBasePtr = std::unique_ptr<StateBase> ;

}
