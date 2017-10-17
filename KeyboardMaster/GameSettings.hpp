#pragma once

#include <string>

namespace KM
{

// prototype
struct GameSettings
{
	std::string name;
	std::string dictionaryFile;

	int gameAreaWidth, gameAreaHeight;
	int fontSize;
};

}