#pragma once

#include "../FrameworkLib/GameBase.hpp"
#include "../FrameworkLib/StateBase.hpp"
#include "WordBlock.hpp"
#include "Dictionary.hpp"

namespace km
{

namespace fw = framework;

class WordsAttackGame : public fw::StateBase
{
public:
    WordsAttackGame(fw::GameBase& game);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

    void textEntered();
    void enterWord();

private:
    void spawnWordBlock();
    void destroyWord();

    std::vector<std::shared_ptr<WordBlock>> wordBlocks_;
    Dictionary dictionary_;

    wchar_t typedLetter_;
    std::wstring typedWord_;

    int lives = 3;
    int missedWords = 0;
    int maxWordsInGame = 5;
    int wordsInGame = 0;

    sf::Clock clock_;

    // GUI
    sf::RectangleShape horizontalLine;
    std::wstring    typingText;
};

}



/*
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <locale>
#include <codecvt>
#include <random>
#include <chrono>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "Application.hpp"
#include "VirtualKeyboard.hpp"
#include "CourseText.hpp"
#include "KeyboardTyper.hpp"
#include "Dictionary.hpp"
#include "Utils.hpp"
#include "Misc.hpp"
#include "WordBlock.hpp"

namespace KM
{

namespace fs = boost::filesystem;

class WordsAttackGame : public Application
{
public:
	virtual int run(int argc, wchar_t** argv)
	{
		const char* appName = "KeyboardMaster";
		const char* courseFile = "data/course_20.txt";
		constexpr int windowWidth = 1024, windowHeight = 768;
		constexpr int gameAreaWidth = 1024, gameAreaHeight = 640;
		constexpr int courseAreaWidth = 1024, courseAreaHeight = 400;
		constexpr int courseLevelMax = 20;
		constexpr int fontSize = 18;
		constexpr int textLineVerticalOffset = 2;


		// get executable path
		fs::path full_path(fs::initial_path<fs::path>());
		full_path = fs::system_complete(fs::path(argv[0]));
		std::string exec_path = full_path.remove_filename().string() + "/";

		// converter string - wstring
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

		// SFML window
		sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), appName);
		window.setFramerateLimit(60);

		// game font
		sf::Font    mainFont;
		mainFont.loadFromFile(exec_path + "media/CourierNew.ttf");

		// background
		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile(exec_path + "media/deep-blue-space.jpg");
		sf::Sprite  backgroundSprite;
		backgroundSprite.setTexture(backgroundTexture);

		// audio
		sf::Sound sound;
		sf::SoundBuffer audioKeytype;
		sf::SoundBuffer audioMistake;
		sf::SoundBuffer audioNewline;
		sf::SoundBuffer audioBell;
		audioKeytype.loadFromFile(exec_path + "media/keytype.wav");
		audioMistake.loadFromFile(exec_path + "media/mistake.wav");
		audioNewline.loadFromFile(exec_path + "media/newline.wav");
		audioBell.loadFromFile(exec_path + "media/bell.wav");

		// player
		int playerLives = 5;
		int playerScore = 0;
		float playerSpeed = 5.f;
		int maxWordsInGame = 5;
		float timeFactor = 1.0f;
//		float gameAreaWidth= 1024.f;		
		int	playerHorizontalTarget = 0;


		sf::Texture playerTexture;
		sf::Sprite	playerSprite;
		playerTexture.loadFromFile(exec_path + "media/Eagle.png");
		playerSprite.setTexture(playerTexture);
		playerSprite.setPosition( gameAreaWidth / 2.f, gameAreaHeight + 32.f);


		sf::Texture		bulletTexture;
		bulletTexture.loadFromFile(exec_path + "media/bullet.png");
		sf::Sprite		bulletSprite;
		bulletSprite.setTexture(bulletTexture);


		// GUI elements /////////////////////////////////////////////////////////////////////////////////
		sf::Text	nextLetterText;
		nextLetterText.setFont(mainFont);
		nextLetterText.setString("");
		nextLetterText.setCharacterSize(28);
		nextLetterText.setColor(sf::Color::Yellow);
		nextLetterText.setStyle(sf::Text::Bold);
		nextLetterText.setPosition(980, 30);

		sf::Text	typedWordText;
		typedWordText.setFont(mainFont);
		typedWordText.setString("");
		typedWordText.setCharacterSize(28);
		typedWordText.setColor(sf::Color::Yellow);
		typedWordText.setStyle(sf::Text::Bold);
		typedWordText.setPosition(800, 60);

		sf::Text	debugText;
		debugText.setFont(mainFont);
		debugText.setString("Debug:");
		debugText.setCharacterSize(16);
		debugText.setColor(sf::Color::Red);
		debugText.setStyle(sf::Text::Bold);
		debugText.setPosition(780, 500);

		sf::Text	typedText;
		typedText.setFont(mainFont);
		typedText.setCharacterSize(24);
		typedText.setColor(sf::Color::White);
		typedText.setStyle(sf::Text::Bold);
		typedText.setPosition(40, gameAreaHeight);


		// Dictionary for game, load all words to
		Dictionary dictw;
		dictw.loadFromFile(converter.from_bytes(exec_path + "data/all_words_easy.txt"));

		// words objects
		typedef std::unique_ptr<WordBlock> WordBlockPtr;

		std::vector<WordBlockPtr> wordsBlocksPtrList;

		for (int i = 0; i < maxWordsInGame; ++i)
		{
			int wordLength = RandomMachine::getRange(dictw.shortestWord, dictw.longestWord);
			std::wstring wordGenerated = dictw.randomWord(wordLength);
			wordsBlocksPtrList.push_back(WordBlockPtr(new WordBlock(i, wordGenerated, sf::Vector2f(0, 1), sf::Color::Blue, mainFont)));
		}

		// initialize words blocks objects

		int currentletter = 0;
		int currentword = 0;

		int correct = 0;
		int mistakes = 0;
		int missedWords = 0;

		// int wordLength = 0;
		// std::string typingWord;
		// setup starting letter

		// currently typed text by user
		std::wstring	typingText;
		std::wstring	typedWord;
		wchar_t nextLetter;

		//nextLetter = dictw.lines[currentline][currentletter];
		//nextLetterText.setString(nextLetter);
		//vkb.highlightLetter(static_cast<int>(nextLetter));

		int keysTyped = 0;
		float kpm = 0;
		float correctness = 100.f;
		wchar_t typedLetter;

		// main clocks starts with the game
		sf::Clock clock;
		clock.restart();

		sf::RectangleShape	line(sf::Vector2f(1024, 5));
		line.setPosition(sf::Vector2f{ 0, (float)gameAreaHeight });

		int lastWordSpawn = 0;

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
						typingText.pop_back();
					}
					else if (static_cast<int>(typedLetter) == KeyCode::Enter)
					{
						typedWord = typingText;
						typedWordText.setString(typedWord);
						typingText.clear();

						// SEND word to all words object, destroy if found the same
						bool miss = true;
						for (auto& w : wordsBlocksPtrList)
						{
							if (w->word == typedWord)
							{
								w->isAlive = false;
								lastWordSpawn = w->spawn;
								playerScore += w->word.length();
								miss = false;

								playerHorizontalTarget = w->shape.getPosition().x;
								std::wcout << "target: " << playerHorizontalTarget << std::endl;

								break;
							}
						}
						if (miss)
							missedWords++;
					}
					else
					{
						keysTyped++; // every key

						typingText.push_back(typedLetter);

						// calculate KPM after key typed (or each seconds)
						sf::Time keyPressedTime = clock.getElapsedTime();
						kpm = 60.f / keyPressedTime.asSeconds() * keysTyped;
					}

					break;
				default:
					break;
				}

			}

			// logic
			{
				typedText.setString(typingText.c_str());

				std::wstringstream wss;
				std::wstring debugString;
				wss << L"Time: " << clock.getElapsedTime().asSeconds()
					<< L"\nCorrect: " << correct << L" Miss: " << mistakes
					<< L"\nLetter: " << currentletter//<< L" Line: " << currentline
													 // << L"\nd.currentline.s: " << dictw.lines[currentline].size()
					<< L"\nd.lines.s: " << dictw.lines.size()
					<< L"\ntotalKeysTyped: " << keysTyped
					<< L"\nKPM: " << kpm
					<< L"\nLetters count: " << dictw.lettersCount
					<< L"\nWords count: " << dictw.wordsCount
					<< L"\nCorrectness: " << correctness
					<< L"\nPlayer score: " << playerScore
					<< L"\nPlayer lives: " << playerLives;

				debugText.setString(wss.str());


				for (auto& w : wordsBlocksPtrList)
				{
					w->update();
					if (w->shape.getPosition().y >= gameAreaHeight) {
						w->isAlive = false;
						--playerLives;
						lastWordSpawn = w->spawn;
					}

				}

				wordsBlocksPtrList.erase(
					std::remove_if(wordsBlocksPtrList.begin(), wordsBlocksPtrList.end(),
						[](WordBlockPtr& w) { return !w->isAlive; }),
					wordsBlocksPtrList.end());

				// create new
				if (wordsBlocksPtrList.size() < maxWordsInGame)
				{
					int wordLength = RandomMachine::getRange(dictw.shortestWord, dictw.longestWord);
					std::wstring wordGenerated = dictw.randomWord(wordLength);

					// speed up every 10 seconds
					float timeFactor = (int)(clock.getElapsedTime().asSeconds() / 10.f) * 0.1f;

					wordsBlocksPtrList.push_back(
						WordBlockPtr(new WordBlock(lastWordSpawn, wordGenerated, sf::Vector2f(0, 1 + timeFactor), sf::Color::Blue, mainFont))
						);
				}

				if (playerLives <= 0)
				{
					window.close();
				}
				else
				{
					// player movement
				}


			}

			// draw section
			{
				window.clear();

				window.draw(backgroundSprite);

				window.draw(playerSprite);
				window.draw(typedText);
				window.draw(line);

				for (auto& w : wordsBlocksPtrList)
				{
					window.draw(w->shape);
					window.draw(w->wordText);
				}

				window.draw(typedWordText);
				window.draw(debugText);
				window.display();
			}
		}

		sf::Time elapsedGameTime = clock.getElapsedTime();
		std::wcout << L"Program finished after " << elapsedGameTime.asSeconds() << L" seconds." << std::endl;
		std::wcout << L"KPM: " << kpm << " SCORE:" << playerScore << std::endl;
		return 0;
	}
};

}
*/