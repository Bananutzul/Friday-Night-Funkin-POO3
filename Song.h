#pragma once

#include <SFML/Audio.hpp>
#include <cstring>
#include "Chart.h"

using namespace std;

class Song {
private:
    string name;
    sf::Music instrumental;
    sf::Music bfVoice;
    sf::Music dadVoice;
    Chart chart;
public:
    Song();
    Song(string name, const string& instr, const string& bf, const string& dad, const Chart& chart_temp);

    void play();
    void stop();
    float getTimeMs();
    bool isPlaying();
    Chart getChart() const;
    string getName() const;
    float getSpeedMultiplier() const;
    int getBpm() const;

    void pause();
};