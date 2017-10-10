#pragma once

#include <map>
#include <iostream>
#include <memory>
//#include <SFML\Graphics.hpp>
#include "GameState.hpp"

namespace framework
{

/*	Simple State manager
	- holds all game states objects
	- there is no transitions defined, every state can go to everyone
*/
class StateManager
{
public:
	StateManager(sf::RenderWindow& renderWindow);// = default;
	StateManager(const StateManager&) = delete;
	StateManager(StateManager&&) = delete;
	~StateManager() = default;

	void addState(const GameStatePtr& gs);

	// before start, there's needs to be at least one state
	void start();	

	void changeState(std::string state);
	
	void handleEvent(const sf::Event& event);
	void update(float dt);
	void draw();

private:
	sf::RenderWindow&	renderWindow_;

	std::map<std::string, GameState>	statesMap_;	// map or vector?
	std::vector<GameStatePtr>	states_;
	GameStatePtr	current_;
};



} // framework