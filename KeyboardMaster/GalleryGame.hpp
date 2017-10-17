#pragma once
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
#include "PictureElement.hpp"

namespace KM
{

namespace fs = boost::filesystem;

class GalleryGame : public Application
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

		// picture
		sf::Texture pictureTexture;
		pictureTexture.loadFromFile(exec_path + "media/forest.png");
		sf::Sprite pictureSprite;
		pictureSprite.setTexture(pictureTexture);

		
		// audio
		sf::Sound sound;
		sf::SoundBuffer audioKeytype; audioKeytype.loadFromFile(exec_path + "media/keytype.wav");
		sf::SoundBuffer audioMistake; audioMistake.loadFromFile(exec_path + "media/mistake.wav");
		sf::SoundBuffer audioNewline; audioNewline.loadFromFile(exec_path + "media/newline.wav");
		sf::SoundBuffer audioBell; audioBell.loadFromFile(exec_path + "media/bell.wav");

		// player
		//int playerLives = 5;
		//int playerScore = 0;
		//float playerSpeed = 5.f;
		//int maxWordsInGame = 5;
		//float timeFactor = 1.0f;
		//int	playerHorizontalTarget = gameAreaWidth / 2.f;


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

		int tempActiveIndex = 0;

		typedef std::unique_ptr<PictureElement> PictureElementPtr;
		std::vector<PictureElementPtr> pictureElementsList;

		int pictureElementsRows = 4;
		int pictureElementsCols = 5;
		int pictureElementsNum = pictureElementsRows * pictureElementsCols;	// 20
		int peWidth = pictureTexture.getSize().x / pictureElementsCols;
		int peHeight = pictureTexture.getSize().y / pictureElementsRows;

		for (int i = 0; i < pictureElementsNum; ++i)
		{
			int wordLength = RandomMachine::GetRange(dictw.shortestWord, dictw.longestWord);
			std::wstring wordGenerated = dictw.randomWord(wordLength);
			sf::Sprite pes = sf::Sprite(pictureTexture, sf::IntRect(i % pictureElementsCols * peWidth, i % pictureElementsRows *peHeight, peWidth, peHeight));

			pictureElementsList.push_back(PictureElementPtr(new PictureElement(i, wordGenerated, sf::Vector2f(i % pictureElementsCols * peWidth, i % pictureElementsRows *peHeight), mainFont, pes)));
		}
		// initialize words blocks objects
		pictureElementsList.at(tempActiveIndex)->activate();

		int currentletter = 0;
		int currentword = 0;

		int correct = 0;
		int mistakes = 0;
		int missedWords = 0;
		int missedPictures = 0;

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

		int revealedElements = 0;

		// LOOP
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
						for (auto& pe : pictureElementsList)
						{
							if (pe->word == typedWord)
							{
								miss = false;
								pe->isRevealed = true;
								revealedElements++;
								//lastWordSpawn = w->spawn;
								//playerScore += w->word.length();
								// set next active element, TODO: random
								// TODO: timer
								if (tempActiveIndex < 20) {
									tempActiveIndex++;
									pictureElementsList.at(tempActiveIndex)->activate();
								}
									

								std::wcout << "revealed: " << pe->index << std::endl;

								break;
							}
							

						}
						if (miss)
						{
							missedWords++;
							pictureElementsList.at(tempActiveIndex)->isActive = false;
							tempActiveIndex++;
						}
							
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
					<< L"\nMissed pictures: " << missedPictures;

				debugText.setString(wss.str());

				
				for (auto& pe : pictureElementsList)
				{
					pe->update();
				}

				// end game
				if (revealedElements == pictureElementsNum)
					window.close();

			}

			// draw section
			{
				window.clear();

				//window.draw(pictureSprite);

				window.draw(typedText);
				//window.draw(line);

				for (auto& pe : pictureElementsList)
				{
					if(pe->isRevealed)
						window.draw(pe->sprite);
					else if (pe->isActive)
						window.draw(pe->wordText);
				}

				window.draw(typedWordText);
				window.draw(debugText);
				window.display();
			}
		}

		sf::Time elapsedGameTime = clock.getElapsedTime();
		std::wcout << L"Program finished after " << elapsedGameTime.asSeconds() << L" seconds." << std::endl;
		std::wcout << L"KPM: " << kpm << std::endl;
		return 0;
	}
};

}
*/