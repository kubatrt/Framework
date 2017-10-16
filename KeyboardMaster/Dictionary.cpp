#include "Dictionary.hpp"

namespace KM
{

// http://www.cplusplus.com/reference/locale/
// http://www.cplusplus.com/reference/locale/codecvt/

std::wstring LoadUtf8FileToString(const char* filename)
{
    LOG("Opening file: " << filename);
    std::wifstream wif(filename);
    if(wif.is_open())
    {
        std::wcout << "wifstream open" << std::endl;
    }
    std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
    std::cout << loc.name() << std::endl;
    //wif.imbue(loc);
    
    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}


Dictionary::Dictionary()
{
    shortestWord = 3;
    longestWord = 0;
    lettersCount = 0;
    wordsCount = 0;
}

void Dictionary::loadFromFile(const char* filename)
{
    text = LoadUtf8FileToString(filename);
    std::wcout << "Loaded text: " << text << std::endl;    
    
    prepareWords();
    prepareLines();
    
    for (auto& line : lines)
    {
        lettersCount += line.length();
    }

    for (auto& w : words)
    {
        if(w.length() != 0)
            wordsByLength[w.length()].push_back(w);
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

std::wstring Dictionary::getRandomWord(int length)
{
    return wordsByLength[length].at(RandomMachine::GetRange<size_t>(0, wordsByLength[length].size() - 1));
}

void Dictionary::prepareLines()
{
    std::wstring buffer;
    for (std::wstring::iterator it = text.begin(); it != text.end(); ++it)
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
    for (std::wstring::iterator it = text.begin(); it != text.end(); ++it)
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