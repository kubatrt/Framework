#pragma once

#include "CourseGame.hpp"

namespace km
{

const char* courseFile = "data/texts-pl";
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
    , dictionary_(courseFile)
{
    clock_.restart();

    audioKeytype.loadFromFile("media/keytype.wav");
    audioMistake.loadFromFile("media/mistake.wav");
    audioNewline.loadFromFile("media/newline.wav");
    audioBell.loadFromFile("media/bell.wav");

    mainFont_.loadFromFile("media/CourierNew.ttf");

    backgroundTexture.loadFromFile("media/deep-blue-space.jpg");
    backgroundSprite.setTexture(backgroundTexture);

    vkb_.layoutTexture.loadFromFile("media/kbl_48.png");
    vkb_.layoutSprite.setTexture(vkb_.layoutTexture);
    vkb_.layoutSprite.setPosition(0, windowHeight - vkb_.layoutTexture.getSize().y);
    vkb_.maskTexture.loadFromFile("media/mask.png");
    vkb_.maskSprite.setTexture(vkb_.maskTexture);
    vkb_.maskSprite.setColor(sf::Color(255, 255, 255, 100));

    nextLetterText.setFont(mainFont_);
    nextLetterText.setString("");
    nextLetterText.setCharacterSize(32);
    nextLetterText.setFillColor(sf::Color::Yellow);
    nextLetterText.setStyle(sf::Text::Bold);
    nextLetterText.setPosition(980, 30);

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

    nextLetter = dictionary_.getLines()[currentline][currentletter];
    nextLetterText.setString(nextLetter);
    vkb_.highlightLetter(static_cast<int>(nextLetter));
}

CourseGame::~CourseGame()
{
    sf::Time elapsedGameTime = clock_.getElapsedTime();
    std::wcout << L"Program finished after " << elapsedGameTime.asSeconds() << L" seconds." << std::endl;
    std::wcout << L"KPM: " << kpm << std::endl;
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
        break;
    case sf::Event::TextEntered:

        typedLetter = static_cast<wchar_t>(event.text.unicode);
        std::wcout << L"debug ASCII character typed: " << static_cast<int>(typedLetter) << std::endl;

        if (static_cast<int>(typedLetter) == KeyCode::Backspace)
        {

            if (currentletter > 0)
            {
                backspaces++;
                currentletter--;
                typingText.pop_back();
                courseInputTextLines[currentline].setString(typingText);
            }

            nextLetter = dictionary_.getLines()[currentline][currentletter];
            nextLetterText.setString(nextLetter);
        }
        else if (static_cast<int>(typedLetter) == KeyCode::Enter)
        {
            if (currentline < dictionary_.getLines().size() - 1)	// can we go down?
            {
                omittedLetters = dictionary_.getLines()[currentline].size() - currentletter;
                std::wcout << "omitted: " << omittedLetters << std::endl;

                // move to new line
                currentline++;
                typingText.clear();
                currentletter = 0;

                mainSound_.setBuffer(audioNewline);
                mainSound_.play();

                nextLetter = dictionary_.getLines()[currentline][currentletter];
                nextLetterText.setString(nextLetter);

                // TODO we should consider ommited letters in line
            }
            else
            {
                // end course with "enter" key which is correct
                if (currentletter == dictionary_.getLines()[currentline].size())
                {
                    std::wcout << "END2" << std::endl;
                    game_.popState();
                }
            }
        }
        else
        {
            keysTyped++; // every key

                         // if current letter is still in current line?
            if (currentletter < dictionary_.getLines()[currentline].size())
            {

                typingText.push_back(typedLetter);
                courseInputTextLines[currentline].setString(typingText);

                if (typedLetter == nextLetter)
                {

                    // prevent counting backspaced letters
                    if (backspaces > 0)
                    {
                        backspaces--;
                    }
                    else
                    {
                        correct++;
                    }
                    mainSound_.setBuffer(audioKeytype);
                    mainSound_.play();
                }
                else
                {
                    mistakes++;
                    mainSound_.setBuffer(audioMistake);
                    mainSound_.play();
                }

                currentletter++;

                nextLetter = dictionary_.getLines()[currentline][currentletter];

                if (static_cast<int>(nextLetter) == 0)
                    nextLetterText.setString("NL"); // new line
                else if (static_cast<int>(nextLetter) == KeyCode::Space)
                    nextLetterText.setString("_");	// space
                else
                    nextLetterText.setString(nextLetter);

                //std::wcout << "typedLetter: " << static_cast<int>(typedLetter) << std::endl;
                //std::wcout << "nextLetter: " << static_cast<int>(nextLetter) << std::endl;
            }
            else
            {
                std::wcout << "last letter in line" << std::endl;
                if (currentline < dictionary_.getLines().size() - 1)
                {
                    // the correct movement to next line are only "space" or "Enter" (earlier)
                    if (static_cast<int>(typedLetter) == KeyCode::Enter)
                    {
                        mainSound_.setBuffer(audioNewline);
                        mainSound_.play();
                    }
                    else
                    {
                        mistakes++;
                        mainSound_.setBuffer(audioMistake);
                        mainSound_.play();

                    }

                    // move to new line
                    currentline++;
                    typingText.clear();
                    currentletter = 0;

                    nextLetter = dictionary_.getLines()[currentline][currentletter];
                    nextLetterText.setString(nextLetter);
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
            kpm = 60.f / keyPressedTime.asSeconds() * keysTyped;
        }

        // calculate correctness
        correctness = (mistakes == 0 && omittedLetters == 0) ?
            100.f : 100.f - (static_cast<float>(mistakes + omittedLetters)
                / dictionary_.getLettersCount() * 100.f);

        vkb_.highlightLetter(static_cast<int>(nextLetter));
        break;
    default:
        break;
    }
}

void CourseGame::update(sf::Time deltaTime)
{
    std::wstringstream wss;
    std::wstring debugString;
    wss << L"Time: " << clock_.getElapsedTime().asSeconds()
        << L"\nCorrect: " << correct << L" Miss: " << mistakes
        << L"\nLetter: " << currentletter << L" Line: " << currentline
        << L"\nd.currentline.s: " << dictionary_.getLines()[currentline].size()
        << L"\nd.lines.s: " << dictionary_.getLines().size()
        << L"\ntotalKeysTyped: " << keysTyped
        << L"\nKPM: " << kpm
        << L"\nLetters count: " << dictionary_.getLettersCount()
        << L"\nWords count: " << dictionary_.getWordsCount()
        << L"\nCorrectness: " << correctness;


    debugText.setString(wss.str());
}

void CourseGame::draw(sf::RenderTarget& renderer)
{
    renderer.draw(backgroundSprite);
    renderer.draw(vkb_.layoutSprite);
    renderer.draw(vkb_.maskSprite);

    for (std::vector<sf::Text>::const_iterator it = courseTextLines.begin(); it != courseTextLines.end(); ++it)
    {
        renderer.draw(*it);
    }

    for (std::vector<sf::Text>::const_iterator it = courseInputTextLines.begin(); it != courseInputTextLines.end(); ++it)
    {
        renderer.draw(*it);
    }

    //window.draw(nextLetterText);
    renderer.draw(debugText);
}

}
