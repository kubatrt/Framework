#pragma once

#include <vector>

namespace KM
{

struct KeyboardTyper
{
	// sf::Clock   clock;

	unsigned int keysTyped;
	unsigned int wordsTyped;

	float kpm;  // keys per minute
	float kpw;  // keys per word

	//std::vector<Word>   words;
	float getKPM() { return kpm; }
	float getKPW() { return kpw; }

	void start() {};
	void pause() {};
	void stop() {};
};

}	// KM