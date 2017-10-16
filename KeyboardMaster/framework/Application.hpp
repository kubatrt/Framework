#pragma once

#include <SFML/Graphics.hpp>

namespace KM
{

typedef sf::RenderWindow Graphics;
typedef sf::Event	Event;

enum class InputType { Keyboard, Mouse, Touch };
enum class GameEvent { Pause, Resume };


class Applicatoin
{
	virtual void OnStartup() = 0;
	virtual void OnShutdown() = 0;
	virtual void OnUpdate(float) = 0;
	virtual void OnDraw(const Graphics&) = 0;
	virtual void OnEvent(const Event& event) = 0;
	virtual void OnInput(const Event& input) = 0;
};

}