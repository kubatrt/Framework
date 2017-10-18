#pragma once

#include "CourseGame.hpp"


namespace KM
{

//namespace fs = boost::filesystem;

int CourseGame::run(int argc, char* argv)
{
    const char* appName = "KeyboardMaster";
    const char* courseFile = "data/texts-pl";
    constexpr int windowWidth = 1024, windowHeight = 768;
    constexpr int gameAreaWidth = 1024, gameAreaHeight = 640;
    constexpr int courseAreaWidth = 1024, courseAreaHeight = 400;
    constexpr int courseLevelMax = 20;
    constexpr int fontSize = 18;
    constexpr int textLineVerticalOffset = 2;

    // get executable path
    //fs::path full_path(fs::initial_path<fs::path>());
    //	FIXME
//		full_path = fs::system_complete(fs::path(std::string(argv[0])));
    std::string exec_path = ""; // "D:\\Workspace\\Projects\\Framework\\Debug";//full_path.remove_filename().string() + "/";
    std::cout << "exec_path = " << exec_path << std::endl;


    // converter string - wstring
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    // SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), appName);
    window.setFramerateLimit(60);


    // game UI objects
    sf::Font    mainFont;
    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;

    // play all buffers by one audio /temp/
    sf::Sound sound;
    sf::SoundBuffer audioKeytype; audioKeytype.loadFromFile(exec_path + "media/keytype.wav");
    sf::SoundBuffer audioMistake; audioMistake.loadFromFile(exec_path + "media/mistake.wav");
    sf::SoundBuffer audioNewline; audioNewline.loadFromFile(exec_path + "media/newline.wav");
    sf::SoundBuffer audioBell; audioBell.loadFromFile(exec_path + "media/bell.wav");


    // currently typed text by user
    std::wstring	typingText;

    // graphics 
    mainFont.loadFromFile(exec_path + "media/CourierNew.ttf");

    backgroundTexture.loadFromFile(exec_path + "media/deep-blue-space.jpg");
    backgroundSprite.setTexture(backgroundTexture);

    // Virtualkeyboard
    Virtualkeyboard vkb;
    vkb.layoutTexture.loadFromFile(exec_path + "media/kbl_48.png");
    vkb.layoutSprite.setTexture(vkb.layoutTexture);
    vkb.layoutSprite.setPosition(0, windowHeight - vkb.layoutTexture.getSize().y);
    vkb.maskTexture.loadFromFile(exec_path + "media/mask.png");
    vkb.maskSprite.setTexture(vkb.maskTexture);
    vkb.maskSprite.setColor(sf::Color(255, 255, 255, 100));

    sf::Text	nextLetterText;
    nextLetterText.setFont(mainFont);
    nextLetterText.setString("");
    nextLetterText.setCharacterSize(32);
    nextLetterText.setFillColor(sf::Color::Yellow);
    nextLetterText.setStyle(sf::Text::Bold);
    nextLetterText.setPosition(980, 30);

    sf::Text	debugText;
    debugText.setFont(mainFont);
    debugText.setString("Debug:");
    debugText.setCharacterSize(16);
    debugText.setFillColor(sf::Color::Red);
    debugText.setStyle(sf::Text::Bold);
    debugText.setPosition(780, 500);
    
    //if(!fs::exists(courseFile))
    //    LOG("FILE DOESNT EXISTS!");

    Dictionary dictw;
    dictw.loadFromFile(courseFile);

    //CourseText courseText(dictw);
    int currentline = 0;
    int currentletter = 0;
    int currentword = 0;
    int correct = 0;
    int mistakes = 0;

    std::vector<sf::Text> courseTextLines;
    std::vector<sf::Text> courseInputTextLines;

    // create lines of text for this course
    for (int i = 0; i < dictw.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont);
        textField.setString(dictw.getLines()[i]);   // must be 'L'
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::White);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, i * (fontSize * 2) + textLineVerticalOffset);

        courseTextLines.push_back(textField);
    }
    // same for user input text, but empty
    for (int i = 0; i < dictw.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont);
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::Cyan);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, i * (fontSize * 2) + textLineVerticalOffset + fontSize);

        courseInputTextLines.push_back(textField);
    }

    // int wordLength = 0;
    // std::string typingWord;
    // setup starting letter

    wchar_t nextLetter;
    nextLetter = dictw.getLines()[currentline][currentletter];
    nextLetterText.setString(nextLetter);
    vkb.highlightLetter(static_cast<int>(nextLetter));

    int omittedLetters = 0;
    int keysTyped = 0;
    float kpm = 0;
    float correctness = 100.f;
    wchar_t typedLetter;
    int backspaces = 0;

    // main clocks starts with the game
    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::LostFocus:
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
            case sf::Event::TextEntered:

                typedLetter = static_cast<wchar_t>(event.text.unicode);
                std::wcout << L"ASCII character typed: " << static_cast<int>(typedLetter) << std::endl;

                if (static_cast<int>(typedLetter) == KeyCode::Backspace)
                {

                    if (currentletter > 0)
                    {
                        backspaces++;
                        currentletter--;
                        typingText.pop_back();
                        courseInputTextLines[currentline].setString(typingText);
                    }

                    nextLetter = dictw.getLines()[currentline][currentletter];
                    nextLetterText.setString(nextLetter);
                }
                else if (static_cast<int>(typedLetter) == KeyCode::Enter)
                {
                    if (currentline < dictw.getLines().size() - 1)	// can we go down?
                    {
                        omittedLetters = dictw.getLines()[currentline].size() - currentletter;
                        std::wcout << "omitted: " << omittedLetters << std::endl;

                        // move to new line
                        currentline++;
                        typingText.clear();
                        currentletter = 0;

                        sound.setBuffer(audioNewline);
                        sound.play();

                        nextLetter = dictw.getLines()[currentline][currentletter];
                        nextLetterText.setString(nextLetter);

                        // TODO we should consider ommited letters in line
                    }
                    else
                    {
                        // end course with "enter" key which is correct
                        if (currentletter == dictw.getLines()[currentline].size())
                        {
                            std::wcout << "END2" << std::endl;
                            window.close();
                        }
                    }
                }
                else
                {
                    keysTyped++; // every key

                                 // if current letter is still in current line?
                    if (currentletter < dictw.getLines()[currentline].size())
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
                            else {
                                correct++;
                            }
                            sound.setBuffer(audioKeytype);
                            sound.play();
                        }
                        else
                        {
                            mistakes++;
                            sound.setBuffer(audioMistake);
                            sound.play();
                        }

                        currentletter++;

                        nextLetter = dictw.getLines()[currentline][currentletter];

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
                        if (currentline < dictw.getLines().size() - 1)
                        {
                            // the correct movement to next line are only "space" or "Enter" (earlier)
                            if (static_cast<int>(typedLetter) == KeyCode::Enter)
                            {
                                sound.setBuffer(audioNewline);
                                sound.play();
                            }
                            else
                            {
                                mistakes++;
                                sound.setBuffer(audioMistake);
                                sound.play();

                            }

                            // move to new line
                            currentline++;
                            typingText.clear();
                            currentletter = 0;

                            nextLetter = dictw.getLines()[currentline][currentletter];
                            nextLetterText.setString(nextLetter);
                        }
                        // this means that was last letter in last line in course and it's incorrect, but dont count mistake
                        else
                        {
                            std::wcout << "END" << std::endl;
                            window.close();
                        }
                    }

                    // calculate KPM after key typed (or each seconds)
                    sf::Time keyPressedTime = clock.getElapsedTime();
                    kpm = 60.f / keyPressedTime.asSeconds() * keysTyped;


                }

                // calculate correctness
                correctness = (mistakes == 0 && omittedLetters == 0) ? 100.f 
					: 100.f - (static_cast<float>(mistakes + omittedLetters) / dictw.getLettersCount() * 100.f);

                vkb.highlightLetter(static_cast<int>(nextLetter));

                break;
            default:
                break;
            }

        }

        // logic
        {
            //typedText.setString(typingText.c_str());

            std::wstringstream wss;
            std::wstring debugString;
            wss << L"Time: " << clock.getElapsedTime().asSeconds()
                << L"\nCorrect: " << correct << L" Miss: " << mistakes
                << L"\nLetter: " << currentletter << L" Line: " << currentline
                << L"\nd.currentline.s: " << dictw.getLines()[currentline].size()
                << L"\nd.lines.s: " << dictw.getLines().size()
                << L"\ntotalKeysTyped: " << keysTyped
                << L"\nKPM: " << kpm
                << L"\nLetters count: " << dictw.getLettersCount()
                << L"\nWords count: " << dictw.getWordsCount()
                << L"\nCorrectness: " << correctness;


            debugText.setString(wss.str());
        }

        // draw section
        {
            window.clear();

            window.draw(backgroundSprite);
            window.draw(vkb.layoutSprite);
            window.draw(vkb.maskSprite);

            for (std::vector<sf::Text>::const_iterator it = courseTextLines.begin(); it != courseTextLines.end(); ++it)
            {
                window.draw(*it);
            }

            for (std::vector<sf::Text>::const_iterator it = courseInputTextLines.begin(); it != courseInputTextLines.end(); ++it)
            {
                window.draw(*it);
            }

            //window.draw(nextLetterText);
            window.draw(debugText);
            window.display();
        }
    }

    sf::Time elapsedGameTime = clock.getElapsedTime();
    std::wcout << L"Program finished after " << elapsedGameTime.asSeconds() << L" seconds." << std::endl;
    std::wcout << L"KPM: " << kpm << std::endl;
    return 0;
}
}

