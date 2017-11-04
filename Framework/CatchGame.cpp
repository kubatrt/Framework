#include "CatchGame.hpp"
#include "MainMenu.hpp"
#include "CourseMenu.hpp"
#include "../FrameworkLib/ResourceManager/ResourceManager.hpp"

namespace example
{

CatchGame::CatchGame()
    : fw::BaseGame({ 1280, 720 }, "Catch game")
{
    window_.setFramerateLimit(60);  // instead of separate fixedUpdate
    pushState<MainMenu>(*this);
    //pushState<CourseMenu>(*this);

    //fw::ResourceManager<sf::Font>::get("arial");
}

void CatchGame::update(sf::Time deltaTime)
{
    auto& state = getCurrentState();
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
    //constexpr unsigned ticksPerSecond = 60;	//ticks per seconds for fixedTimeUpdate
    //const sf::Time timePerUpdate = sf::seconds(1.f / static_cast<float>(ticksPerSecond));
    //unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    //auto lag = sf::Time::Zero;

    while (window_.isOpen() )
    {
        // TODO: (time) move elsewhere
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        //lag += elapsed;

        // Real time update
        update(elapsed); 

        // Fixed time update
        /*while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            auto& state = getCurrentState();
            state.fixedUpdate(elapsed);
        }*/

        // Render
        draw(window_);

        //Handle window events
        handleEvents();
        tryPop();
    }

    return 0;
}

}
