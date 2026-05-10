#include "Song.h"
#include "Exceptions.h"

#include <SFML/Audio.hpp>
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

Song::Song() {
    name = "N/A";
}

Song::Song(string name, const string& instr, const string& bf, const string& dad, const Chart& chart_temp) {
    this->name = name;
    chart = chart_temp;

    try {
        if (!instrumental.openFromFile(instr))
            throw InvalidOptionException("Instrumental File not available!");

        if (!bfVoice.openFromFile(bf))
            throw InvalidOptionException("BF File not available!");

        if (!dadVoice.openFromFile(dad))
            throw InvalidOptionException("Dad File not available!");
    } catch (const InvalidOptionException& e) {
        cout << "ERROR: " << e.what() << '\n';
    }
}

void Song::play() {
    instrumental.play();
    bfVoice.play();
    dadVoice.play();
}

void Song::stop() {
    instrumental.stop();
    bfVoice.stop();
    dadVoice.stop();
}

float Song::getTimeMs() {
    return instrumental.getPlayingOffset().asMilliseconds();
}

bool Song::isPlaying() {
    return instrumental.getStatus() == sf::Music::Status::Playing;
}

Chart Song::getChart() const {
    return chart;
}

string Song::getName() const {
    return name;
}

