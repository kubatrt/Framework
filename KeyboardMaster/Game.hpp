#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "GameStateManager.hpp"

namespace KM
{

// prototype
struct GameSettings
{
	std::string name;
	std::string dictionaryFile;
	
	int gameAreaWidth, gameAreaHeight;
	int fontSize;
};

// placeholders
class Graphics; 
class Event;

typedef unsigned int StateID;

//class Game : State


class Game 
{
public:
	Game() {};
	Game(const Game&) = delete;
	Game& operator=(Game const&) = delete;
	Game(int idleState) {};
	virtual ~Game() {};

	virtual void OnStartup() {};
	virtual void OnShutdown() {};

	virtual void OnUpdate(float deltaTime) {};
	virtual void OnDraw(const Graphics& window) {};
	virtual void OnEvent(const Event& event) {};
	virtual void OnInput(const Event& input) {};

private:
	std::unique_ptr<GameStateManager> gameStateManager;
};

class SfmlGame : public Game
{
	virtual void OnUpdate(float deltaTime) {};
	virtual void OnDraw(const sf::RenderWindow& window) {};
	virtual void OnEvent(const sf::Event& event) {};
	virtual void OnInput(const sf::Event& input) {};
};

}