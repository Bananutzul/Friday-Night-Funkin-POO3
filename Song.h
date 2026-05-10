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
    Song(string name, const string& audio_filename, const Chart& chart);
    Song(const Song& obj);
    Song& operator=(const Song& obj);

    void play();
    void stop();
    float getTimeMs();
};