#include "CatchGame.hpp"
#include "MainMenu.hpp"
#include "CourseMenu.hpp"

namespace example
{

CatchGame::CatchGame(sf::RenderWindow& window)
    : fw::BaseGame(window)
{
    window_.setFramerateLimit(60);  // instead separate fixedUpdate
    pushState<MainMenu>(*this);
    //pushState<CourseMenu>(*this);
}

void CatchGame::update(sf::Time deltaTime)
{
    auto& state = getCurrentState();
    state.draw(window_);
    state.handleInput();
    state.update(deltaTime);

    fpsCounter_.update(deltaTime);
}

void CatchGame::draw(sf::RenderTarget& renderer)
{
    window_.clear();

    auto& state = getCurrentState();
    state.draw(window_);
    fpsCounter_.draw(window_);

    window_.display();
}

int CatchGame::run()
{
    constexpr unsigned ticksPerSecond = 60;	//ticks per seconds
    const sf::Time timePerUpdate = sf::seconds(1.f / static_cast<float>(ticksPerSecond));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    while (window_.isOpen() /*&& !states_.empty()*/)
    {
        auto& state = getCurrentState();

        // TODO: (time) move elsewhere
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        // Real time update
        update(elapsed); 

        // Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;

            state.fixedUpdate(elapsed);
        }

        //Render
        draw(window_);

        //Handle window events
        handleEvents();
        tryPop();
    }

    return 0;
}

}
