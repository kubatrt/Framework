#pragma once

// Types

struct Rectangle
{
	sf::RectangleShape shape;

	Rectangle() {}

	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getSize().x / 2.f; }
	float right() const noexcept { return x() + shape.getSize().x / 2.f; }
	float top() const noexcept { return y() - shape.getSize().y / 2.f; }
	float bottom() const noexcept { return y() + shape.getSize().y / 2.f; }
};

struct PictureElement : public Rectangle
{
	std::wstring	word;
	sf::Text		wordText;

	PictureElement() {}
};

struct User
{
	std::string name;
	unsigned int courseLevel;   // 0 - 20
};

// player's game representative
// in some game mode's there wont be any!
struct Player
{
	sf::Texture texture;
	sf::Sprite  sprite;
};

struct GameSession
{
	int score;
	int lives;
	float time;
};

class IGameEntity
{
	virtual void update() = 0;
	virtual void draw() = 0;
};

class ILetterTyped
{
public:
	virtual void typedLetter(const wchar_t letter) = 0;
};

class IWordTyped
{
public:
	virtual void typedWord(const std::wstring word) = 0;
};

