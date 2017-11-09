#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include "../FrameworkLib/Utilities.hpp"


namespace km
{

// Class responsible for loading words from file, UTF-8
class Dictionary
{
public:
    Dictionary(const std::string& filePath);
    ~Dictionary();
    Dictionary(const Dictionary&) = delete;
    const Dictionary& operator=(const Dictionary) = delete;
    Dictionary(Dictionary&&) = delete;
    Dictionary&& operator=(Dictionary&&) = delete;

    void loadFromFile(const std::string& filePath);
    void printAllWords();
    std::wstring randomWord(int length);

    const std::wstring getText() const { return text_; }
    const std::vector<std::wstring> getLines() const { return lines_; }
    const std::set<std::wstring> getWords() const { return words_; }
    unsigned int getLettersCount() const { return lettersCount_; }
    unsigned int getWordsCount() const { return wordsCount_; }
    unsigned int getLongestWord() const { return longestWord_; }
    unsigned int getShortestWord() const { return shortestWord_; }

private:
    void prepareLines();
    void prepareWords();
    void sortWordsByLength();
    void prepareCount();

    unsigned int lettersCount_;
    unsigned int wordsCount_;
    unsigned int longestWord_;
    unsigned int shortestWord_;

    std::wstring text_;
    std::vector <std::wstring> lines_;
    std::set <std::wstring> words_;
    std::map<int, std::vector<std::wstring>> wordsByLength_;
};

}
