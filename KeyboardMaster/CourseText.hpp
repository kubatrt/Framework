#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Dictionary.hpp"

namespace km
{

namespace unussed
{

// Structure for text typed for player
struct CourseText
{
	sf::Font font;

	std::wstring text;
	unsigned int currentLetter;

	int correct;
	int mistakes_;

	CourseText(const Dictionary& dictw)
	{
		currentLetter = 0;
		text = dictw.getText();

		mistakes_ = 0;
		correct = 0;
	}

	void checkLetter(const wchar_t& l)
	{
		if (l == text[currentLetter]) {
			currentLetter++;
			correct++;
		}
		else
		{
			mistakes_++;
		}
	}

	bool isFinished() 
	{ 
		return currentLetter == text.size(); 
	}

	wchar_t getLetter() 
	{ 
		return text[currentLetter]; 
	}

	int getLength() 
	{ 
		return text.size(); 
	}
};

}
}
