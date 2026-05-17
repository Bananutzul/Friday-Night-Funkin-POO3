#pragma once

#include "json.hpp"
#include "Arrow.h"
#include <vector>
#include <cstring>

using json = nlohmann::json;
using namespace std;

struct Note {
    float time;
    Direction direction;
    float duration; // > 0 -> hold note
};

class Chart {
private:
    vector<Note> player_notes;
    vector<Note> opponent_notes;
    string difficulty;
    float speedMultiplier;
    int bpm;
public:
    Chart();
    Chart(const string& filename, string difficulty);
    Chart(const Chart& obj);
    Chart& operator=(const Chart& obj);

    vector<Note> getPlayerNotes() const;
    vector<Note> getOpponentNotes() const;
    float getSpeedMultiplier() const;
    int getBpm() const;
};


