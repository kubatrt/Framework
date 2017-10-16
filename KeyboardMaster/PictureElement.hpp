#pragma	once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Miscellaneous.hpp"

namespace KM
{
	class PictureElement : public Rectangle
	{
	private:
		static const int charFontSize = 22;
		static const int charWidth = 14;
		static const int charHeight = 24;

	public:
		std::wstring	word;
		wchar_t			nextLetter;

		sf::Text		wordText;
		sf::Sprite		sprite;

		bool isActive;
		bool isRevealed;
		bool isMissed;
		int index;

		// fontSize, 
		// 24, 15
		// 22, 14
		// 18, 12
		size_t getWordLength() { return word.length(); }

		sf::Clock	timer;
		float timeToDestroy = 3.f;


		PictureElement(int index, std::wstring word, sf::Vector2f pos, sf::Font& font, sf::Sprite elementSprite)
		{
			isMissed = false;
			timer.restart();
			this->index = index;
			this->word = word;
			nextLetter = word.front();
			isRevealed = false;
			isActive = false;

			wordText.setFont(font);
			wordText.setString(word);
			wordText.setCharacterSize(charFontSize);
			wordText.setColor(sf::Color::White);
			wordText.setStyle(sf::Text::Bold);
			wordText.setOrigin(0, 0);
			wordText.setPosition(sf::Vector2f( pos.x + elementSprite.getTextureRect().width / 2.f , pos.y + elementSprite.getTextureRect().height/ 2.f));

			sprite = elementSprite;
			sprite.setPosition(pos);

			//shape.setSize(sf::Vector2f(word.length() * charWidth, charHeight));

			std::wcout << "create wordblock:" << word << std::endl;
		}

		// WordBlock(const WordBlock& wordBlock) = default;
		PictureElement(const PictureElement& wordBlock)
		{
			std::wcout << "copy constructor: " << word << std::endl;
		}

		~PictureElement()
		{
			std::wcout << "destroy wordblock:" << word << std::endl;
		}

		void activate()
		{
			isActive = true;
			timer.restart();
		}

		void update()
		{
			if (isActive && (timer.getElapsedTime().asSeconds() >= timeToDestroy))
			{
				isMissed = true;
			}
		}
	};

}
