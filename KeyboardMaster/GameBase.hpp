#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GameStateManager.hpp"

namespace KM
{

class GameBase
{
public:
	GameBase() : gsm_() {};
	GameBase(int idleState) {};
	
	GameBase(const GameBase&) = delete;
	GameBase& operator=(GameBase const&) = delete;
	
	virtual ~GameBase() {};

	virtual void OnStartup() {};
	virtual void OnShutdown() {};

	virtual void OnUpdate(float deltaTime) {};
	virtual void OnDraw(const sf::RenderTarget& window) {};
	virtual void OnEvent(const sf::Event& event) {};
	virtual void OnInput(const sf::Event& input) {};

private:
	std::unique_ptr<GameStateManager> gsm_;
};
	
}	// KM