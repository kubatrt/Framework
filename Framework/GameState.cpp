#include <algorithm>
#include "GameSate.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"

namespace example
{

GameState::GameState(fw::BaseGame& game)
    : StateBase(game)
    , dropLastTime_(sf::Time::Zero)
    , dropInterval_(sf::seconds(2.f))
{
    initPlayer();
    
    dropBox({100.f, 30.f}, 0.5f);
    dropBox({game.getWindow().getSize().x - 100.f, 30.f }, 0.5f);

    scoreText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    scoreText_.setCharacterSize(16);
    scoreText_.setStyle(sf::Text::Regular);
    scoreText_.setPosition({20.f, 50.f});

    livesText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    livesText_.setCharacterSize(16);
    livesText_.setStyle(sf::Text::Regular);
    livesText_.setPosition({20.f, 80.f});
}

void GameState::initPlayer()
{
    float playerWidth = 200.f;
    player_.rect.shape = sf::RectangleShape{ sf::Vector2f(playerWidth, 40.f) };
    player_.rect.shape.setPosition({ game_.getWindow().getSize().x / 2.f, game_.getWindow().getSize().y - 60.f });
    player_.rect.shape.setFillColor(sf::Color::Blue);
    player_.lives = 3;
    player_.speed = 20.f;
    player_.score = 0;
}

void GameState::handleEvent(sf::Event e)
{
    handleInput(e);

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
        {
            std::cout << "quit" << std::endl;
            game_.popState();
        }
    default:
        break;
    }
}

void GameState::handleInput(sf::Event e)
{
    // TODO: currently in handleEvent
    sf::Vector2f velocity;
    if(sf::Keyboard::isKeyPressed( sf::Keyboard::Left))
    {
        velocity = { -player_.speed, 0};
        std::cout << "Left" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity = { player_.speed, 0 };
        std::cout << "Right" << std::endl;
    }
    else
        velocity = {0,0};

    player_.rect.shape.move(velocity);
}

void GameState::dropBox(sf::Vector2f position, float speed)
{
    Box box{ position, speed };
    boxes_.push_back(box);   // by copy
}

void GameState::checkCollisions()
{
    for (auto& box : boxes_)
    {
        if (collision2d(Point{box.rect.x(), box.rect.y()}, player_.rect))
        {
            box.destroyed = true;
            player_.score += 100;
        }
        if (box.rect.bottom() <= 0)
        {
            box.destroyed = true;
            player_.lives--;
        }
    }


 
}

void GameState::destroyBoxes()
{
    boxes_.erase(std::remove_if(boxes_.begin(), boxes_.end(), 
        [](auto& box){ return box.destroyed; }), boxes_.end());
}

void GameState::update(sf::Time deltaTime)
{
    dropLastTime_ += deltaTime;
    if (dropLastTime_ > dropInterval_)
    {
        int minX = 0 + (boxSize / 2);
        int maxX = game_.getWindow().getSize().x - (boxSize / 2);
        float locationX = fw::RandomMachine::getRange<int>(48, game_.getWindow().getSize().x - 48);
        float speed = fw::RandomMachine::getRange<int>(1, 10) * 0.4f;

        dropBox({locationX, 30.f}, speed);
        dropLastTime_ = sf::Time::Zero;
    }

    for (auto& box : boxes_)
    {
        box.update(deltaTime);
    }

    checkCollisions();
    destroyBoxes();

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
    for (auto& box : boxes_)
    {
        renderer.draw(box.rect.shape);
    }
    renderer.draw(player_.rect.shape);

    renderer.draw(scoreText_);
    renderer.draw(livesText_);
}

}
