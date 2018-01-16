#pragma once

#include "CourseGame.hpp"

namespace km
{

constexpr int 
    windowWidth = 1024,
    windowHeight = 768,
    gameAreaWidth = 1024,
    gameAreaHeight = 640,
    courseAreaWidth = 1024,
    courseAreaHeight = 400,
    courseLevelMax = 20,
    fontSize = 18,
    textLineVerticalOffset = 2;


CourseGame::CourseGame(fw::GameBase& game)
    : StateBase(game)
    , dictionary_("data/texts-pl")
{
    clock_.restart();


    mainFont_.loadFromFile("media/CourierNew.ttf");

    backgroundTexture.loadFromFile("media/deep-blue-space.jpg");
    backgroundSprite.setTexture(backgroundTexture);

    vkb_.layoutTexture.loadFromFile("media/kbl_48.png");
    vkb_.layoutSprite.setTexture(vkb_.layoutTexture);
    vkb_.layoutSprite.setPosition(0.f, static_cast<float>(windowHeight - vkb_.layoutTexture.getSize().y));
    vkb_.maskTexture.loadFromFile("media/mask.png");
    vkb_.maskSprite.setTexture(vkb_.maskTexture);
    vkb_.maskSprite.setColor(sf::Color(255, 255, 255, 100));

    //nextLetterText.setFont(mainFont_);
    //nextLetterText.setString("");
    //nextLetterText.setCharacterSize(32);
    //nextLetterText.setFillColor(sf::Color::Yellow);
    //nextLetterText.setStyle(sf::Text::Bold);
    //nextLetterText.setPosition(980, 30);

    debugText.setFont(mainFont_);
    debugText.setString("Debug:");
    debugText.setCharacterSize(16);
    debugText.setFillColor(sf::Color::Red);
    debugText.setStyle(sf::Text::Bold);
    debugText.setPosition(780, 500);

    //CourseText courseText(dictw);


    // create lines of text for this course
    for (int i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setString(dictionary_.getLines()[i]);   // must be 'L'
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::White);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, i * (fontSize * 2) + textLineVerticalOffset);
        courseTextLines.push_back(textField);
    }

    // same for user input text, but empty
    for (int i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::Cyan);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, i * (fontSize * 2) + textLineVerticalOffset + fontSize);
        courseInputTextLines.push_back(textField);
    }

    // int wordLength = 0;
    // std::string typingWord;
    // setup starting letter

    nextLetter_ = dictionary_.getLines()[currentline_][currentletter_];
    //nextLetterText.setString(nextLetter_);
    vkb_.highlightLetter(static_cast<int>(nextLetter_));
}

CourseGame::~CourseGame()
{
    sf::Time elapsedGameTime = clock_.getElapsedTime();
    std::wcout << L"Program finished after " << elapsedGameTime.asSeconds() << L" seconds." << std::endl;
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
            textEntered();
        break;
    default:
        break;
    }
}

void CourseGame::textEntered()
{
    std::wcout << L"debug ASCII character typed: " << static_cast<int>(typedLetter_) << std::endl;

    if (static_cast<int>(typedLetter_) == KeyCode::Backspace)
    {
        backspace();
        nextLetter_ = dictionary_.getLines()[currentline_][currentletter_];
        //nextLetterText.setString(nextLetter_);
    }
    else if (static_cast<int>(typedLetter_) == KeyCode::Enter)
    {
        if (currentline_ < dictionary_.getLines().size() - 1)    // can we go down?
        {
            omittedLetters_ = dictionary_.getLines()[currentline_].size() - currentletter_;
            std::wcout << "omitted: " << omittedLetters_ << std::endl;

            moveToNewLine();
            soundPlayer_.play("newline");

            nextLetter_ = dictionary_.getLines()[currentline_][currentletter_];
            //nextLetterText.setString(nextLetter_);

            // TODO ommited letters in line
        }
        else
        {
            // end course with "enter" key which is correct
            if (currentletter_ == dictionary_.getLines()[currentline_].size())
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
            typingText.push_back(typedLetter_);
            courseInputTextLines[currentline_].setString(typingText);

            if (typedLetter_ == nextLetter_)
            {
                // prevent counting backspaced letters
                if (backspaces_ > 0)
                    backspaces_--;
                else
                    correct_++;
                soundPlayer_.play("keytype");
            }
            else
            {
                mistakes_++;
                soundPlayer_.play("mistake");
            }

            currentletter_++;
            nextLetter_ = dictionary_.getLines()[currentline_][currentletter_];


            //if (static_cast<int>(nextLetter_) == 0)
            //    nextLetterText.setString("NL"); // new line
            //else if (static_cast<int>(nextLetter_) == KeyCode::Space)
            //    nextLetterText.setString("_");  // space
            //else
            //    nextLetterText.setString(nextLetter_);

            //std::wcout << "typedLetter: " << static_cast<int>(typedLetter) << std::endl;
            //std::wcout << "nextLetter: " << static_cast<int>(nextLetter) << std::endl;
        }
        else
        {
            std::wcout << "last letter in line" << std::endl;
            if (currentline_ < dictionary_.getLines().size() - 1)
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
                currentline_++;
                typingText.clear();
                currentletter_ = 0;

                nextLetter_ = dictionary_.getLines()[currentline_][currentletter_];
                nextLetterText.setString(nextLetter_);
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
    correctnessPercentage_ = (mistakes_ == 0 && omittedLetters_ == 0) ?
        100.f : 100.f - (static_cast<float>(mistakes_ + omittedLetters_)
            / dictionary_.getLettersCount() * 100.f);
}

void CourseGame::backspace()
{
    if (currentletter_ > 0)
    {
        backspaces_++;
        currentletter_--;
        typingText.pop_back();
        courseInputTextLines[currentline_].setString(typingText);
    }
}

void CourseGame::moveToNewLine()
{
    currentline_++;
    typingText.clear();
    currentletter_ = 0;
}

void CourseGame::prepareDebugText()
{
    std::wstringstream wss;
    wss << L"Time: " << clock_.getElapsedTime().asSeconds()
        << L"\nCorrect: " << correct_ << L" Miss: " << mistakes_
        << L"\nLetter: " << currentletter_ << L" Line: " << currentline_
        << L"\nd.currentline.s: " << dictionary_.getLines()[currentline_].size()
        << L"\nd.lines.s: " << dictionary_.getLines().size()
        << L"\ntotalKeysTyped: " << keysTyped_
        << L"\nKPM: " << kpm_
        << L"\nLetters count: " << dictionary_.getLettersCount()
        << L"\nWords count: " << dictionary_.getWordsCount()
        << L"\nCorrectness: " << correctnessPercentage_;
    debugText.setString(wss.str());
}

void CourseGame::update(sf::Time deltaTime)
{
    prepareDebugText();
}

void CourseGame::draw(sf::RenderTarget& renderer)
{
    renderer.draw(backgroundSprite);
    renderer.draw(vkb_.layoutSprite);
    renderer.draw(vkb_.maskSprite);

    for (sf::Text text : courseTextLines)
    {
        renderer.draw(text);
    }
    for (sf::Text text : courseInputTextLines)
    {
        renderer.draw(text);
    }

    //window.draw(nextLetterText);
    renderer.draw(debugText);
}

}
