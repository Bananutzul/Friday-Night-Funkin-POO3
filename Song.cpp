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

Song::Song(string name, const string& audio_filename, const Chart& chart_temp) {
    this->name = name;
    chart = chart_temp;

    try {
        if (!audio_file.openFromFile(audio_filename))
            throw InvalidOptionException("File not available!");
        audio_file.openFromFile(audio_filename);
    } catch (const InvalidOptionException& e) {
        cout << "ERROR: " << e.what() << '\n';
    }
    }