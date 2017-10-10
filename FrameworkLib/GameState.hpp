#pragma once

#include <memory>
#include <vector>
#include <functional>
//#include <SFML/Graphics.hpp>

#include "State.hpp"

namespace sf
{
	class RenderWindow;
	class Event; // ::EventType;
	//enum Event::EventType;
}

namespace framework
{

class StateManager;
class GameState;

class GameState : public IState
{
public:
	GameState() = default;
	GameState(StateManager& sm, const std::string& name) 
		: sm_(sm)
		, name_(name)
	{}
	GameState(const GameState&) = default;	// should be deleted
	virtual ~GameState() = default;

	std::string getName() { return name_; }

	virtual void onEnter() { std::cout << "onEnter" << std::endl; };
	virtual void onExit() { std::cout << "onExit" << std::endl; };

	virtual void onPlay() {};
	virtual void onPause() {};
	virtual void onStop() {};

	virtual void handleEvent(const sf::Event& event) {};
	virtual void update(float dt) {};
	virtual void draw(sf::RenderWindow&) {};

protected:
	StateManager& sm_;
	//std::map<sf::Event::EventType, std::function<void(const sf::Event& data)>> eventHandlers_;
	std::string name_;
};

using GameStatePtr = std::shared_ptr<GameState>;
using GameStateWPtr = std::weak_ptr<GameState>;


}	// framework