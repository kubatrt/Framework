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
	virtual void onStartup() = 0;
	virtual void onShutdown() = 0;
	virtual void onUpdate(float) = 0;
	virtual void onDraw(const Graphics&) = 0;
	virtual void onEvent(const Event& event) = 0;
	virtual void onInput(const Event& input) = 0;
};

}