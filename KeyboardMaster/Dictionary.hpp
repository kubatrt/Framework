#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <codecvt>
#include <locale>
#include "Utilities.hpp"


namespace KM
{

// Class responsible for loading words from file, UTF-8
class Dictionary
{
public:
    Dictionary();
    Dictionary(const Dictionary&) = delete;
    const Dictionary& operator=(const Dictionary) = delete;

	void loadFromFile(const char* filename);
	void printAllWords();
	std::wstring randomWord(int length);

	
	std::vector <std::wstring> lines;
	std::set <std::wstring> words;
	std::map<int, std::vector<std::wstring>>	wordsByLength;	//	is this will be helpfull??
	
	const std::wstring getText() const { return text_; }
	int lettersCount;
	int wordsCount;
	int longestWord;
	int shortestWord;
	
private:
    void prepareLines();
	void prepareWords();

	std::wstring text_;
};

}

