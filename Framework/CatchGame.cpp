#include "CatchGame.hpp"
#include "States/StateMenu.hpp"


CatchGame::CatchGame()
	: window_({1280, 720}, "GameNameHere")
{
    window_.setFramerateLimit(60);
    pushState<StateMenu>(*this);
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
    auto lag      = sf::Time::Zero;

    while (window_.isOpen() && !states_.empty())
    {
        auto& state = getCurrentState();

        //Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        //Real time update
		update(elapsed); 

        //Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            
			state.fixedUpdate(elapsed);
        }

        //Render
        draw(window_);

        //Handle window events
        handleEvent();
        tryPop();
    }

	return 0;
}

void CatchGame::close()
{
	window_.close();
}

void CatchGame::tryPop()
{
    if (shouldPopState_)
    {
        states_.pop_back();
    }
}

void CatchGame::handleEvent()
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
                break;

        }
    }
}

StateBase& CatchGame::getCurrentState()
{
    return *states_.back();
}

void CatchGame::popState()
{
    shouldPopState_ = true;
}

const sf::RenderWindow& CatchGame::getWindow() const
{
    return window_;
}