#pragma once

#include <SFML/Audio.hpp>
#include <cstring>
#include "Chart.h"

using namespace std;

class Song {
private:
    string name;
    sf::Music audio_file;
    Chart chart;
public:
    Song();
    Song(string name, const string& audio_filename, const Chart& chart_temp);
    // Song(const Song& obj);
    // Song& operator=(const Song& obj); sf::Music nu poate fi copiat, asa ca nu putem folosi copy constr sau operatorul =

    void play();
    void stop();
    float getTimeMs();
};