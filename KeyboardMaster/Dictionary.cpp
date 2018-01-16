#include "Dictionary.hpp"
#include "../FrameworkLib/Util/Files.hpp"
#include "Misc.hpp"

namespace km
{

Dictionary::Dictionary(FilePath filePath)
    : shortestWord_(3)
    , longestWord_(8)
    , lettersCount_(0)
    , wordsCount_(0)
{
    loadFromFile(filePath);

    std::wcout << "Loaded text: " << textFromFile_ << std::endl;
    std::wcout << "letters count: " << lettersCount_ << std::endl;
    std::wcout << "longest word: " << longestWord_ << std::endl;
    std::wcout << "shortest word: " << shortestWord_ << std::endl;
}

void Dictionary::loadFromFile(FilePath filePath)
{
    textFromFile_ = framework::loadTextFromUtf8File(filePath);
    prepareWords();
    prepareLines();
    prepareCount();
    sortWordsByLength();
}

void Dictionary::prepareCount()
{
	for (auto& line : lines_)
	{
		lettersCount_ += line.length();
	}
}

void Dictionary::sortWordsByLength()
{
	for (auto& word : words_)
	{
		if (word.length() != 0)
			wordsByLength_[word.length()].push_back(word);
	}
}

void Dictionary::printAllWords()
{
    for (auto& w : words_)
    {
        std::wcout << w << " ";
    }
    std::wcout << std::endl;
}

std::wstring Dictionary::getRandomWord()
{
    return wordsAll_.at( framework::RandomMachine::getRange<size_t>(0, wordsAll_.size() - 1) );
}

std::wstring Dictionary::getRandomWord(int length)
{
    return wordsByLength_[length].at(
        framework::RandomMachine::getRange<size_t>(0, wordsByLength_[length].size() - 1));
}

void Dictionary::prepareLines()
{
    std::wstring buffer;
    for (std::wstring::iterator it = textFromFile_.begin(); it != textFromFile_.end(); ++it)
    {
        if (*it == '\n')
        {
            lines_.push_back(buffer);
            buffer.clear();
        }
        else
        {
            buffer.push_back(*it);
        }
    }
    lines_.push_back(buffer);
}

void Dictionary::prepareWords()
{
    std::wstring buffer;
    for (std::wstring::iterator it = textFromFile_.begin(); it != textFromFile_.end(); ++it)
    {
        if (*it == ' ' || *it == '\n')
        {
            // longest word
            if (buffer.length() > longestWord_)
                longestWord_ = buffer.length();

            // shortest word
            if (buffer.length() != 0 && buffer.length() < shortestWord_)
                shortestWord_ = buffer.length();

            wordsCount_++;
            words_.insert(buffer);
            
            buffer.clear();
        }
        else
        {
            buffer.push_back(*it);
        }
    }

    bool lastWord = !buffer.empty();
    if (lastWord)
    {
        wordsCount_++;
        words_.insert(buffer);
    }

    // just all words
    for(auto word : words_)
    {
        wordsAll_.push_back(word);
    }
}

}