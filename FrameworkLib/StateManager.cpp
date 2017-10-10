#include "StateManager.hpp"
#include <algorithm>
#include <cassert>
#include <string>

namespace framework
{

StateManager::StateManager(sf::RenderWindow& renderWindow)
	: renderWindow_(renderWindow)
{
	
}

void StateManager::start()
{
	if (states_.empty())
	{
		std::cerr << "State manager is empty!" << std::endl;
		return;
	}

	current_ = states_.at(0);
	current_->onEnter();
}

void StateManager::addState(const GameStatePtr& gs)
{
	states_.emplace_back(std::move(gs));
}


void StateManager::changeState(std::string stateName)
{
	bool stateFound = false;
	for (auto state : states_)
	{
		if ((*state).getName() == stateName)
		{
			stateFound = true;
			if (current_ != nullptr)
			{
				current_->onExit();
			}

			current_ = state;
			current_->onEnter();
		}
	}
	
	if (!stateFound)
		std::cerr << stateName << " state not found!" << std::endl;
}

void StateManager::handleEvent(const sf::Event& event)
{
	current_->handleEvent(event);
}

void StateManager::update(float dt)
{
	assert(current_ != nullptr);

	current_->update(dt);
}

void StateManager::draw()
{
	assert(current_ != nullptr);

	current_->draw(renderWindow_);
}

}