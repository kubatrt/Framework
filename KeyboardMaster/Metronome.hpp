#pragma once

#include <iostream>
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>

// TODO
class Metronome
{
public:
    Metronome(unsigned int bpm)
    : bpm_(bpm)
    , isPlaying_(false)
    {
    
    }

    void setBpm(unsigned int bpm) 
    { 
        bpm_ = bpm;
        interval_ = sf::seconds(60.f) / sf::seconds(bpm_);
    }
    unsigned int getBpm() const { return bpm_; }

    void start() 
    {
        clock_.restart();
        isPlaying_ = true;

    }

    void stop() 
    {
        elapsedTime_ = clock_.restart();
        isPlaying_ = false;
    }

    void update(sf::Time deltaTime)
    {
        if(!isPlaying_)
            return;

        sf::Time elapsedTime_ = clock_.getElapsedTime();

        std::cout << elapsedTime_.asSeconds() << std::endl;
       
        if (elapsedTime_.asSeconds() >= interval_)
        {
            elapsedTime_ = sf::Time::Zero;
            playAudio();
        }

    }

private:
    void updateInterval() 
    {
        //interval_ = sf::seconds(60) / bpm_;
    }
    void playAudio() {};

    sf::Clock clock_;
    unsigned int bpm_;
    float interval_;
    bool isPlaying_;
    sf::Time elapsedTime_;


    /*
        BPM - beats per minute
        80 beats per 60 seconds
        interval = 60 / 80 = 0,75 s
    */

};