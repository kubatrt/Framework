#pragma once

#include <SFML\Audio.hpp>

// TODO
class Metronome
{
public:
	Metronome()
		: bpm_(0)
	{}

	void setBpm(unsigned int bpm) { bpm_ = bpm; }
	unsigned int getBpm() const { return bpm_; }

	void start() {}
	void stop() {}

private:
	sf::SoundBuffer	audio_;
	unsigned int bpm_;

};