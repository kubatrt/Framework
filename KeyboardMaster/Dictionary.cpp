#include "Dictionary.hpp"

namespace KM
{

namespace
{
std::wstring LoadUtf8FileToString(const char* filename)
{
	LOG("Opening file: " << filename);

	// http://www.cplusplus.com/reference/locale/
	// http://www.cplusplus.com/reference/locale/codecvt/
	std::wifstream wif(filename);
	if (wif.is_open())
	{
		std::wcout << "wifstream open" << std::endl;
	}

	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	wif.imbue(loc);
	//std::cout << loc.name() << std::endl;

	std::wstringstream wss;
	wss << wif.rdbuf();
	return wss.str();
}
}


Dictionary::Dictionary()
	: shortestWord(3)
	, longestWord(0)
	, lettersCount(0)
	, wordsCount(0)
{
}

void Dictionary::loadFromFile(const char* filename)
{
    text_ = LoadUtf8FileToString(filename);
    std::wcout << "Loaded text: " << text_ << std::endl;    
    
    prepareWords();
    prepareLines();
    
	// prepareCount
    for (auto& line : lines)
    {
        lettersCount += line.length();
    }

	// sortWordsByLength
    for (auto& word : words)
    {
        if(word.length() != 0)
            wordsByLength[word.length()].push_back(word);
    }

    std::wcout << "letters count: " << lettersCount << std::endl;
    std::wcout << "longest word: " << longestWord << std::endl;
    std::wcout << "shortest word: " << shortestWord<< std::endl;
}



void Dictionary::printAllWords()
{
    for (auto& w : words)
    {
        std::wcout << w << " ";
    }
    std::wcout << std::endl;
}

std::wstring Dictionary::randomWord(int length)
{
    return wordsByLength[length].at(RandomMachine::GetRange<size_t>(0, wordsByLength[length].size() - 1));
}

void Dictionary::prepareLines()
{
    std::wstring buffer;
    for (std::wstring::iterator it = text_.begin(); it != text_.end(); ++it)
    {
        if (*it == '\n')
        {
            lines.push_back(buffer);
            buffer.clear();
        }
        else
        {
            buffer.push_back(*it);
        }
    }
    lines.push_back(buffer);
}

void Dictionary::prepareWords()
{
    std::wstring buffer;
    for (std::wstring::iterator it = text_.begin(); it != text_.end(); ++it)
    {
        if (*it == ' ' || *it == '\n')
        {
            if (buffer.length() > longestWord)
                longestWord = buffer.length();

            if (buffer.length() != 0 && buffer.length() < shortestWord)
                shortestWord = buffer.length();

            wordsCount++;
            words.insert(buffer);
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
        wordsCount++;
        words.insert(buffer);
    }
}

}