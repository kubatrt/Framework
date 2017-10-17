#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GameStateManager.hpp"

namespace KM
{

// placeholders
class Graphics; 
class Event;

typedef unsigned int StateID;


class GameBase
{
public:
	GameBase() {};
	GameBase(int idleState) {};
	
	GameBase(const GameBase&) = delete;
	GameBase& operator=(GameBase const&) = delete;
	
	virtual ~GameBase() {};

	virtual void OnStartup() {};
	virtual void OnShutdown() {};

	virtual void OnUpdate(float deltaTime) {};
	virtual void OnDraw(const Graphics& window) {};
	virtual void OnEvent(const Event& event) {};
	virtual void OnInput(const Event& input) {};

private:
	std::unique_ptr<GameStateManager> gameStateManager;
};
	
}	// KM