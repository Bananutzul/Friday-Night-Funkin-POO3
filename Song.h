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
    // Song(const Song& obj);
    // Song& operator=(const Song& obj); sf::Music nu poate fi copiat, asa ca nu putem folosi copy constr sau operatorul =

    void play();
    void stop();
    float getTimeMs();
    bool isPlaying();
    Chart getChart() const;
    string getName() const;
};