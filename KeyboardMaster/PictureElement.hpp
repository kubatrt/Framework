#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "../FrameworkLib/Utilities.hpp"


namespace km
{

// fontSize 24, 15 / 22, 14 / 18, 12

constexpr int charFontSize = 22;
constexpr int charWidth = 14;
constexpr int charHeight = 24;

class Picture;

class PictureElement : public Rectangle
{
public:


    size_t getWordLength() { return word_.length(); }



PictureElement(sf::Sprite element, int index, std::wstring word, sf::Vector2f pos, sf::Vector2f size, )
    : missed_(false)
    , revealed_(false)
    , active_(false)
    , index_(index)
    , word_(word)
    , nextLetter_(word.front())
{
    sf::Font font;
    wordText.setFont(font);
    wordText.setString(word);
    wordText.setCharacterSize(charFontSize);
    wordText.setColor(sf::Color::White);
    wordText.setStyle(sf::Text::Bold);
    wordText.setOrigin(0, 0);
    wordText.setPosition(sf::Vector2f( pos.x + element.getTextureRect().width / 2.f ,
                                       pos.y + element.getTextureRect().height/ 2.f));
    timer_.restart();
    sprite_ = element;
    sprite_.setPosition(pos);

    //shape.setSize(sf::Vector2f(word.length() * charWidth, charHeight));

    log_info("create wordblock:" << word);
}

PictureElement(const PictureElement& pictureElement)
{
    log_info("copy constructor: " << word_);
}

~PictureElement()
{
    log_info("destroy wordblock:" << word_);
}

bool isRevealed() { return revealed_; }
bool isActive() { return active_; }

void reveal()
{
    active_ = true;
    revealed_ = true;
    timer_.restart();
}

void update()
{
    if (active_ && (timer_.getElapsedTime().asSeconds() >= lifeTime))
    {
        missed_ = true;
    }
}

private:
    sf::Sprite sprite_;
    sf::Clock timer_;
    sf::Text wordText;
    std::wstring word_;
    wchar_t nextLetter_;

    bool active_;
    bool revealed_;
    bool missed_;
    int index_;
    float lifeTime = 3.f;
};

}	// KM
