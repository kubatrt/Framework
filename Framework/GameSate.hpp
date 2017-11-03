#pragma once

#include "../FrameworkLib/States/StateBase.hpp"
#include "../FrameworkLib/BaseGame.hpp"
#include "../FrameworkLib/Utilities.hpp"

namespace example
{

namespace fw = framework;

// Game helpers
// TODO: Move
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
    return ((a.x >= b.left() && a.y >= b.top())
        && (a.x < b.right() && a.y < b.bottom()));
}

// Game logic implementation within state
class GameState : public fw::StateBase
{
public:
    GameState(fw::BaseGame& game);

    void handleEvent(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void fixedUpdate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

protected:
    void handleInput(sf::Event e) override;

private:
    void dropBox(sf::Vector2f position, float speed);
    void destroyBoxes();
    void checkCollisions();
    void initPlayer();
    
    
    struct Box
    {
        Rectangle rect;
        float speed;
        bool destroyed;

        Box(sf::Vector2f position, float speed)
        {
            destroyed = false;
            this->speed = speed;
            rect.shape.setPosition(position);
            rect.shape.setSize({ 48.f, 48.f });
            rect.shape.setFillColor(sf::Color::Red);
        }

        void update(sf::Time deltaTime)
        {
            sf::Vector2f velocity{ 0.f, speed };
            rect.shape.move(velocity);
        }
    };

    struct Player
    {
        Rectangle rect;
        unsigned lives;
        unsigned score;
        float speed;
    };


    const unsigned boxSize = 60;

    Player player_;
    std::vector<Box> boxes_;
    sf::Time dropLastTime_;
    sf::Time dropInterval_;

    sf::Font font_;
    sf::Text scoreText_;
    sf::Text livesText_;
};

}
