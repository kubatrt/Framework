#include "KeyboardTyper.hpp"


namespace km
{

KeyboardTyper::KeyboardTyper()
//    : dictionary_("C:\\")
{
    clock_.restart();
} 

KeyboardTyper::~KeyboardTyper()
{

}

void KeyboardTyper::textEnteredEvent(wchar_t letter)
{
    keysTyped_++;
    lastTypedLetter_ = letter;
    typingText_.append({letter});

}

void KeyboardTyper::update()
{

}
inline float KeyboardTyper::correctnessPercentage() 
{
    int lettersCount = 1; // dictionary_.getLettersCount()
    return (mistakes_ == 0 && omittedLetters_ == 0) ? 100.f
    : 100.f - (static_cast<float>((mistakes_ + omittedLetters_)) / lettersCount * 100.f);
}
}