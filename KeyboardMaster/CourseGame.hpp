#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <locale>
#include <codecvt>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "../FrameworkLib/StateBase.hpp"
#include "../FrameworkLib/GameBase.hpp"
#include "VirtualKeyboard.hpp"
#include "Dictionary.hpp"
#include "KeyboardTyper.hpp"
#include "CourseText.hpp"
#include "WordBlock.hpp"
#include "Misc.hpp"

namespace km
{

namespace fw = framework;

class CourseGame : public fw::StateBase
{
public:
    CourseGame(fw::GameBase& game);
    ~CourseGame();

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    Virtualkeyboard vkb_;
    Dictionary dictionary_;

    sf::Clock clock_;
    sf::Font mainFont_;
    sf::Sound mainSound_;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::SoundBuffer audioKeytype;
    sf::SoundBuffer audioMistake;
    sf::SoundBuffer audioNewline;
    sf::SoundBuffer audioBell;


    std::wstring typingText;
    sf::Text nextLetterText;
    sf::Text debugText;
    
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::vector<sf::Text> courseTextLines;
    std::vector<sf::Text> courseInputTextLines;
    unsigned int currentline = 0;
    unsigned int currentletter = 0;
    unsigned int currentword = 0;
    unsigned int correct = 0;
    unsigned int mistakes = 0;
    wchar_t nextLetter;
    int omittedLetters = 0;
    int keysTyped = 0;
    float kpm = 0;
    float correctness = 100.f;
    wchar_t typedLetter;
    int backspaces = 0;

};

}

