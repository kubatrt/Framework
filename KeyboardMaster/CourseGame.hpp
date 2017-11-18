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
    void textEntered();
    void prepareDebugText();
    inline sf::Uint32 inPenultimateLine() { return dictionary_.getLines()[currentline_].size() -1; };
    void moveToNewLine();
    void backspace();
    void calculateCoretness();

    struct SoundPlayer
    {
        SoundPlayer()
        {
            // framework::ResourceHolder::get().audio.get
            sounds_["keytype"].loadFromFile("media/keytype.wav");
            sounds_["mistake"].loadFromFile("media/mistake.wav");
            sounds_["newline"].loadFromFile("media/newline.wav");
            sounds_["bell"].loadFromFile("media/bell.wav");
        }

        void play(const std::string sound)
        {
            if (sounds_.count(sound))
            {
                sound_.setBuffer(sounds_[sound]);
                sound_.play();
            }
                
        }
    private:
        std::map<std::string, sf::SoundBuffer> sounds_;
        sf::Sound sound_;
    };
    SoundPlayer soundPlayer_;

    Virtualkeyboard vkb_;
    Dictionary dictionary_;

    sf::Clock clock_;
    sf::Font mainFont_;
    sf::Sound mainSound_;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    std::wstring typingText;
    sf::Text nextLetterText;
    sf::Text debugText;
    
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::vector<sf::Text> courseTextLines;
    std::vector<sf::Text> courseInputTextLines;

    unsigned int currentline_ = 0;
    unsigned int currentletter_ = 0;
    unsigned int currentword_ = 0;
    unsigned int correct_ = 0;
    unsigned int mistakes_ = 0;
    wchar_t nextLetter_;
    int omittedLetters_ = 0;
    int keysTyped_ = 0;
    float kpm_ = 0;
    float correctnessPercentage_ = 100.f;
    wchar_t typedLetter_;
    int backspaces_ = 0;
};

}

