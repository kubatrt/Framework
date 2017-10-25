#pragma once

#include "../FrameworkLib/States/StateBase.hpp"
#include "../FrameworkLib/BaseGame.hpp"
#include "../FrameworkLib/Utilities.hpp"

namespace example
{

namespace fw = framework;

// Helpers

struct Point
{
    float x;
    float y;
};

struct Rectangle
{
    sf::RectangleShape shape;

    float x() const noexcept { return shape.getPosition().x; }
    float y() const noexcept { return shape.getPosition().y; }
    float left() const noexcept { return x() - shape.getSize().x / 2.f; }
    float right() const noexcept { return x() + shape.getSize().x / 2.f; }
    float top() const noexcept { return y() - shape.getSize().y / 2.f; }
    float bottom() const noexcept { return y() + shape.getSize().y / 2.f; }
};

template <typename TPoint, typename TRect>
bool collision2d(TPoint a, TRect b)
{
    return ((a.x >= b.right() && a.y >= b.top())
        && (a.x < b.left() && a.y < b.bottom()));
}

// Game logic implementation within state
class GameState : public fw::StateBase
{
public:
    GameState(fw::BaseGame& game);

    void handleEvent(sf::Event e) override;
    void handleInput() override;
    void update(sf::Time deltaTime) override;
    void fixedUpdate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    const unsigned boxSize = 60;

    struct Box
    {
        Rectangle rect;
        float speed;
        bool markDestroy;
    };

    struct Player
    {
        Rectangle rect;
        unsigned lives;
        unsigned score;
        float speed;
    };

    void dropBox(float locationX, float speed);
    void checkCollisions();

    
    Player  player_;
    std::vector<Box> boxes_;
    
    sf::Time dropInterval_;
    float dropThreshold_;
};

}
