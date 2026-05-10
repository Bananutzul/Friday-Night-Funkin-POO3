#pragma once

#include "json.hpp"
#include "Arrow.h"
#include <vector>

using json = nlohmann::json;

struct Note {
    float time;
    Direction direction;
    float duration; // >= 0 -> hold note
};

class Chart {
private:
    vector<Note> notes;
    string difficulty;
public:
    Chart();
    Chart(const string& filename, string difficulty);
    Chart(const Chart& obj);
    Chart& operator=(const Chart& obj);

    vector<Note> getNotes() const;
};


