#include <algorithm>
#include "GameSate.hpp"


namespace example
{




GameState::GameState(fw::BaseGame& game)
    : StateBase(game)
    , dropThreshold_(3.f) // s
    , dropInterval_(sf::Time::Zero)

{
    player_.rect.shape = sf::RectangleShape{ sf::Vector2f(200.f, 40.f) };
    player_.rect.shape.setPosition({ game_.getWindow().getSize().x / 2.f, game_.getWindow().getSize().y - 60.f });
    player_.rect.shape.setFillColor(sf::Color::Blue);
    player_.lives = 3;
    player_.speed = 20.f;
    player_.score = 0;
}

void GameState::handleEvent(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
        {
            game_.popState();
        }
        else if (e.key.code == sf::Keyboard::Left)
        {            player_.rect.shape.move({ -player_.speed, 0});
            std::cout << "< Left " << player_.rect.x() << std::endl;
        }
        else if (e.key.code == sf::Keyboard::Right)
        {
            player_.rect.shape.move({ player_.speed, 0 });
            std::cout << "> Right " << player_.rect.x() << std::endl;
        }
    default:
        break;
    }
}

void GameState::handleInput()
{

}

void GameState::dropBox(float locationX, float speed)
{
    Box newBox;
    newBox.markDestroy = false;
    newBox.speed = speed;
    newBox.rect.shape.setPosition({locationX, 30.f});
    newBox.rect.shape.setFillColor(sf::Color::Red);
    boxes_.push_back(newBox);
}

void GameState::checkCollisions()
{
    for (auto& box : boxes_)
    {
        if (collision2d(Point{box.rect.x(), box.rect.y()}, player_.rect))
        {
            box.markDestroy = true;
            player_.score += 100;
        }
        if (box.rect.bottom() <= 0)
        {
            box.markDestroy = true;
            player_.lives--;
        }
    }

    //boxes_.erase(std::remove_if(boxes_.begin(), boxes_.end(), 
    //    [](auto& box){ return box.markDestroy; }));
}

void GameState::update(sf::Time deltaTime)
{
    dropInterval_ += deltaTime;
    if (dropInterval_.asSeconds() > dropThreshold_)
    {
        int minX = 0 + (boxSize / 2);
        int maxX = game_.getWindow().getSize().x - (boxSize / 2);
        float location = game_.getWindow().getSize().x; // framework::RandomMachine::getRange(50, 100);
        float speed = 5.f; //fw::RandomMachine::getRange<float>(3, 8);

        dropBox(location, speed);
        dropInterval_ = sf::Time::Zero;
    }

    checkCollisions();

    if (player_.lives <= 0)
    {
        std::cout << "Game score: " << player_.score << std::endl;
        game_.popState();
    }
    
}

void GameState::fixedUpdate(sf::Time deltaTime)
{

}

void GameState::draw(sf::RenderTarget& renderer)
{
    renderer.draw(player_.rect.shape);
    for (auto& box : boxes_)
    {
        renderer.draw(box.rect.shape);
    }
}

}
