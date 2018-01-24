#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "../FrameworkLib/Utilities.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{


class WordBlock : public Rectangle
{
private:
    wchar_t nextLetter_;
    std::wstring word_;

    sf::Vector2f velocity_;

    sf::Text wordText_;
    bool alive_;

public:

    WordBlock(int spawnX, std::wstring word, sf::Vector2f velocity)
        : word_(word)
        , nextLetter_(word.front())
        , velocity_(velocity)
        , alive_(true)
    {
        constexpr uint charFontSize = 22;
        constexpr uint charWidth = 14;
        constexpr uint charHeight = 24;

        int spawn = spawnX;
        this->word_ = word;
        
        this->velocity_ = velocity;
        alive_ = true;

        wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
        wordText_.setString(word);
        wordText_.setCharacterSize(charFontSize);
        wordText_.setFillColor(sf::Color::White);
        wordText_.setStyle(sf::Text::Bold);

        //static float spawnHorizontalPositions[5]{ 0.f, 200.f, 400.f, 600.f, 800.f };
        wordText_.setPosition(static_cast<float>(spawnX), 0.f);

        shape.setPosition(static_cast<float>(spawnX), 0.f);
        shape.setFillColor(sf::Color::Blue); // TODO: random, depend on length
        shape.setSize(sf::Vector2f( static_cast<float>(word.length() * charWidth), static_cast<float>(charHeight)));

        log_info("CTOR wordblock:" << word);
    }

    std::wstring getWord() const { return word_; }

    void setAlive(bool alive) { alive_ = alive; }
    bool isAlive() { return alive_; }
    
    // WordBlock(const WordBlock& wordBlock) = default;
    WordBlock(const WordBlock& wordBlock)
    {
        log_info("CPY constructor: " << word_);
    }

    ~WordBlock()
    {
        log_info("DTOR wordblock:" << word_);
    }

    // fontSize, // 24, 15 // 22, 14 // 18, 12
    size_t getWordLength() { return word_.length(); }

    /*bool checkBoundaries(float windowWidth)
    {
        return false;   // TODO
    }*/

    void update(sf::Time deltaTime)
    {
        shape.move(velocity_);
        wordText_.move(velocity_);
    }

    void draw(sf::RenderTarget& renderer)
    {
        renderer.draw(shape);
        renderer.draw(wordText_);
    }
};

} // km