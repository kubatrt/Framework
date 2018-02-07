#pragma once

#include "CourseGame.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

constexpr int windowWidth = 1024;
constexpr int windowHeight = 768;
constexpr int gameAreaWidth = 1024;
constexpr int gameAreaHeight = 640;
constexpr int courseAreaWidth = 1024;
constexpr int courseAreaHeight = 400;
constexpr int courseLevelMax = 20;
constexpr int fontSize = 18;
constexpr int textLineVerticalOffset = 2;


CourseGame::SoundPlayer::SoundPlayer()
{
    // framework::ResourceHolder::get().audio.get
    sounds_["keytype"] = fw::ResourceHolder::get().sounds.get("keytype");
    sounds_["mistake"] = fw::ResourceHolder::get().sounds.get("mistake");
    sounds_["newline"] = fw::ResourceHolder::get().sounds.get("newline");
    sounds_["bell"] = fw::ResourceHolder::get().sounds.get("bell");
}

void CourseGame::SoundPlayer::play(const std::string sound)
{
    if (sounds_.count(sound))
    {
        sound_.setBuffer(sounds_[sound]);
        sound_.play();
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

CourseGame::CourseGame(fw::GameBase& game)
    : StateBase(game)
    , dictionary_("D:\\Workspace\\Projects\\Framework\\Debug\\data\\texts-pl")
    , vkb_(game.getWindow().getSize())
    , kb_()
{
    clock_.restart();

    mainFont_ = fw::ResourceHolder::get().fonts.get("CourierNew");
    backgroundSpriteUI_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));

    nextLetterTextUI_.setFont(mainFont_);
    nextLetterTextUI_.setString("");
    nextLetterTextUI_.setCharacterSize(32);
    nextLetterTextUI_.setFillColor(sf::Color::Yellow);
    nextLetterTextUI_.setStyle(sf::Text::Bold);
    nextLetterTextUI_.setPosition(980, 30);

    debugTextUI_.setFont(mainFont_);
    debugTextUI_.setString("Debug:");
    debugTextUI_.setCharacterSize(16);
    debugTextUI_.setFillColor(sf::Color::Red);
    debugTextUI_.setStyle(sf::Text::Bold);
    debugTextUI_.setPosition(780, 500);

    prepareTextFields();
    // int wordLength = 0;
    // std::string typingWord;
    // setup starting letter

    nextLetter_ = dictionary_.getLines()[currentLine_][currentletter_];
    nextLetterTextUI_.setString(nextLetter_);
    
    vkb_.highlightLetter(static_cast<int>(nextLetter_));
}


void CourseGame::prepareTextFields()
{
    // create lines of text for this course
    for (uint i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setString(dictionary_.getLines()[i]);   // must be 'L'
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::White);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, static_cast<float>(i * (fontSize * 2.f) + textLineVerticalOffset));
        courseTextLines.push_back(textField);
    }

    // same for user input text, but empty
    for (uint i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::Cyan);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, static_cast<float>(i * (fontSize * 2.f) + textLineVerticalOffset + fontSize));
        courseInputTextLines.push_back(textField);
    }
}


CourseGame::~CourseGame()
{
    std::wcout << L"Program finished after " << clock_.getElapsedTime().asSeconds() << L" seconds." << std::endl;
    std::wcout << L"KPM: " << kpm_ << std::endl;
}

void CourseGame::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Resized:
        break;
    case sf::Event::LostFocus:
        break;
    case sf::Event::GainedFocus:
        break;

    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
        {
            game_.popState();
        }
        else if (event.key.code == sf::Keyboard::F12)
        {
            game_.toggleFullscreen();
        }
        break;
    case sf::Event::TextEntered:
            typedLetter_ = static_cast<wchar_t>(event.text.unicode);
            kb_.textEnteredEvent(typedLetter_);
            textEnteredEvent();
        break;
    default:
        break;
    }
}

void CourseGame::textEnteredEvent()
{
    std::wcout << L"debug ASCII character typed: " << static_cast<int>(typedLetter_) << std::endl;
    
    if (static_cast<int>(typedLetter_) == KeyCode::Backspace)
    {
        backspace();
        nextLetter_ = dictionary_.getLines()[currentLine_][currentletter_];
        //nextLetterTextUI_.setString(nextLetter_);
    }
    else if (static_cast<int>(typedLetter_) == KeyCode::Enter)
    {
        if (currentLine_ < dictionary_.getLines().size() - 1)    // can we go down?
        {
            omittedLetters_ = dictionary_.getLines()[currentLine_].size() - currentletter_;
            std::wcout << "omitted: " << omittedLetters_ << std::endl;

            moveToNewLine();
            soundPlayer_.play("newline");

            nextLetter_ = dictionary_.getLines()[currentLine_][currentletter_];
            //nextLetterTextUI_.setString(nextLetter_);

            // TODO ommited letters in line
        }
        else
        {
            // end course with "enter" key which is correct
            if (currentletter_ == dictionary_.getLines()[currentLine_].size())
            {
                std::wcout << "END2" << std::endl;
                game_.popState();
            }
        }
    }
    else
    {
        keysTyped_++; // count every key

        // if current letter is still in current line?
        if (currentletter_ < inPenultimateLine())
        {
            typingText_.push_back(typedLetter_);
            courseInputTextLines[currentLine_].setString(typingText_);

            if (typedLetter_ == nextLetter_)
            {
                // prevent counting backspaced letters
                if (backspaces_ > 0)
                    backspaces_--;
                else
                    correctLetters_++;

                soundPlayer_.play("keytype");
            }
            else
            {
                mistakes_++;
                soundPlayer_.play("mistake");
            }

            currentletter_++;
            nextLetter_ = dictionary_.getLines()[currentLine_][currentletter_];


            if (static_cast<int>(nextLetter_) == 0)
                nextLetterTextUI_.setString("NL"); // new line
            else if (static_cast<int>(nextLetter_) == KeyCode::Space)
                nextLetterTextUI_.setString("_");  // space
            else
                nextLetterTextUI_.setString(nextLetter_);

            //std::wcout << "typedLetter: " << static_cast<int>(typedLetter) << std::endl;
            //std::wcout << "nextLetter: " << static_cast<int>(nextLetter) << std::endl;
        }
        else
        {
            std::wcout << "last letter in line" << std::endl;
            if (currentLine_ < dictionary_.getLines().size() - 1)
            {
                // the correct movement to next line are only "space" or "Enter" (earlier)
                if (static_cast<int>(typedLetter_) == KeyCode::Enter)
                {
                    soundPlayer_.play("newline");
                }
                else
                {
                    mistakes_++;
                    soundPlayer_.play("mistake");
                }

                // move to new line
                currentLine_++;
                typingText_.clear();
                currentletter_ = 0;

                nextLetter_ = dictionary_.getLines()[currentLine_][currentletter_];
                nextLetterTextUI_.setString(nextLetter_);
            }
            // this means that was last letter in last line in course and it's incorrect, but dont count mistake
            else
            {
                std::wcout << "END" << std::endl;
                game_.popState();
            }
        }

        // calculate KPM after key typed (or each seconds)
        sf::Time keyPressedTime = clock_.getElapsedTime();
        kpm_ = 60.f / keyPressedTime.asSeconds() * keysTyped_;
    }

    calculateCoretness();
    vkb_.highlightLetter(static_cast<int>(nextLetter_));
}


void CourseGame::calculateCoretness()
{
    correctnessPercentage_ = (mistakes_ == 0 && omittedLetters_ == 0) ? 100.f 
        : 100.f - (static_cast<float>(mistakes_ + omittedLetters_)
            / dictionary_.getLettersCount() * 100.f);
}

void CourseGame::backspace()
{
    if (currentletter_ > 0)
    {
        backspaces_++;
        currentletter_--;
        typingText_.pop_back();
        courseInputTextLines[currentLine_].setString(typingText_);
    }
}

void CourseGame::moveToNewLine()
{
    currentLine_++;
    typingText_.clear();
    currentletter_ = 0;
}

void CourseGame::prepareDebugText()
{
    std::wstringstream wss;
    wss << L"Time: " << clock_.getElapsedTime().asSeconds()
        << L"\nCorrect: " << correctLetters_ << L" Miss: " << mistakes_
        << L"\nLetter: " << currentletter_ << L" Line: " << currentLine_
        << L"\nd.currentline.s: " << dictionary_.getLines()[currentLine_].size()
        << L"\nd.lines.s: " << dictionary_.getLines().size()
        << L"\ntotalKeysTyped: " << keysTyped_
        << L"\nKPM: " << kpm_
        << L"\nLetters count: " << dictionary_.getLettersCount()
        << L"\nWords count: " << dictionary_.getWordsCount()
        << L"\nCorrectness: " << correctnessPercentage_;
    debugTextUI_.setString(wss.str());
}

void CourseGame::update(sf::Time deltaTime)
{
    prepareDebugText();
    vkb_.update(deltaTime);
}

void CourseGame::draw(sf::RenderTarget& renderer)
{
    renderer.draw(backgroundSpriteUI_);

    vkb_.draw(renderer);

    for (sf::Text text : courseTextLines)
        renderer.draw(text);
    for (sf::Text text : courseInputTextLines)
        renderer.draw(text);

    //window.draw(nextLetterTextUI_);
    renderer.draw(debugTextUI_);
}

}
