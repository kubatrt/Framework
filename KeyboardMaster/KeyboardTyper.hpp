#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Misc.hpp"
#include "Dictionary.hpp"
#include "../FrameworkLib/Utilities.hpp"

namespace km
{

// TODO What exatly this class should do?
//  - counting mistakes
//  - collecting typed words
//  - calculating stats

class KeyboardTyper : public framework::NonCopyable
{
public:
    KeyboardTyper();
    ~KeyboardTyper();

    float getKPM() const { return keysPerMinute_; }
    float getKPW() const { return wordsPerMinute_; }
    
    float correctnessPercentage();

    void textEnteredEvent(wchar_t letter);
    void wordEntered(std::wstring word);
    void backspace();
    
    void update();

    std::wstring debugInfo() {};

private:
   // Dictionary dictionary_;

    std::vector<std::wstring> typedWords_;
    sf::Clock clock_;

    std::wstring typingText_;

    wchar_t lastTypedLetter_;
    std::wstring lastTypedWord_;

    float correctness_;
    uint correctLetters_;
    uint correctWords_;
    uint wordsTotal_;
    uint backspaces_;
    uint omittedLetters_;
    uint mistakes_;

    unsigned int keysTyped_;    // every key typed
    unsigned int wordsTyped_;
    float keysPerMinute_;
    float wordsPerMinute_;
};

} // km