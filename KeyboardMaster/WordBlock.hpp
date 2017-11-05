#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"


namespace KM
{

class WordBlock : public Rectangle
{
private:
	float spawnHorizontalPositions[5] { 0.f, 200.f, 400.f, 600.f, 800.f };
	static const int charFontSize = 22;
	static const int charWidth = 14;
	static const int charHeight = 24;

public:
	std::wstring	word;
	wchar_t			nextLetter;

	sf::Vector2f	velocity;
	sf::Text		wordText;
	
	bool isAlive;
	int spawn;

	// fontSize, // 24, 15 // 22, 14 // 18, 12
	size_t getWordLength() { return word.length(); }
	
	WordBlock(int spawnPosition, std::wstring word, sf::Vector2f velocity, sf::Color color, sf::Font& font)
	{	
		spawn = spawnPosition;
		this->word = word;
		nextLetter = word.front();
		this->velocity = velocity;
		isAlive = true;

		wordText.setFont(font);
		wordText.setString(word);
		wordText.setCharacterSize(charFontSize);
		wordText.setFillColor(sf::Color::White);
		wordText.setStyle(sf::Text::Bold);
		wordText.setPosition(spawnHorizontalPositions[spawn], 0.f);
		shape.setPosition(spawnHorizontalPositions[spawn], 0.f);
		shape.setFillColor(color);
		shape.setSize(sf::Vector2f( word.length() * charWidth, charHeight));

		std::wcout << "create wordblock:" << word << std::endl;
	}
	
	// WordBlock(const WordBlock& wordBlock) = default;
	WordBlock(const WordBlock& wordBlock)
	{
		std::wcout << "copy constructor: " << word << std::endl;
	}

	~WordBlock()
	{
		std::wcout << "destroy wordblock:" << word << std::endl;
	}


	bool checkBoundaries(float windowWidth)
	{
		//if (bottom() > windowWidth)
		//	return false; // fall of the bottom
		return true;
	}

	void update()
	{
		shape.move(velocity);
		wordText.move(velocity);
	}
};

}	// KM