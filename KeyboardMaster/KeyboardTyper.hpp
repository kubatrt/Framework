#pragma once

#include <vector>

namespace KM
{

class KeyboardTyper
{
public:
	// sf::Clock   clock;
	//std::vector<Word>   words;
	
	float getKPM() { return kpm; }
	float getKPW() { return kpw; }

	void start() {};
	void pause() {};
	void stop() {};

private:
	unsigned int keysTyped;
	unsigned int wordsTyped;
	float kpm;  // keys per minute
	float kpw;  // keys per word
};

}	// KM