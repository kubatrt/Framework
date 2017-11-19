#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <SFML\System.hpp>
#include "../FrameworkLib/Utilities.hpp"
#include "Misc.hpp"


namespace km
{

// Class responsible for loading words from file, UTF-8
class Dictionary
{
public:
    Dictionary(FilePath filePath);
    ~Dictionary() = default;
    Dictionary(const Dictionary&) = delete;
    const Dictionary& operator=(const Dictionary) = delete;
    Dictionary(Dictionary&&) = delete;
    Dictionary&& operator=(Dictionary&&) = delete;

    void loadFromFile(FilePath filePath);
    void printAllWords();
    std::wstring getRandomWord(int length);

    const std::wstring getText() const { return text_; }
    const std::vector<std::wstring> getLines() const { return lines_; }
    const std::set<std::wstring> getWords() const { return words_; }
    uint getLettersCount() const { return lettersCount_; }
    uint getWordsCount() const { return wordsCount_; }
    uint getLongestWord() const { return longestWord_; }
    uint getShortestWord() const { return shortestWord_; }

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
