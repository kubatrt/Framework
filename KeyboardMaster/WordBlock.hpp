#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"


namespace km
{
constexpr uint charFontSize = 22;
constexpr uint charWidth = 14;
constexpr uint charHeight = 24;

class WordBlock : public Rectangle
{
private:

public:
    std::wstring word;
    wchar_t nextLetter;

    sf::Vector2f velocity;
    sf::Text wordText;

    bool isAlive;
    int spawn;

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

        float spawnHorizontalPositions[5]{ 0.f, 200.f, 400.f, 600.f, 800.f };
        wordText.setPosition(spawnHorizontalPositions[spawn], 0.f);

        shape.setPosition(spawnHorizontalPositions[spawn], 0.f);
        shape.setFillColor(color);
        shape.setSize(sf::Vector2f( word.length() * charWidth, charHeight));

        log_info("CTOR wordblock:" << word);
    }
    
    // WordBlock(const WordBlock& wordBlock) = default;
    WordBlock(const WordBlock& wordBlock)
    {
        log_info("CPY constructor: " << word);
    }

    ~WordBlock()
    {
        log_info("DTOR wordblock:" << word);
    }

    // fontSize, // 24, 15 // 22, 14 // 18, 12
    size_t getWordLength() { return word.length(); }

    bool checkBoundaries(float windowWidth)
    {
        return false;
    }

    void update()
    {
        shape.move(velocity);
        wordText.move(velocity);
    }
};

} // km