#include "Chart.h"
#include <cstring>
#include <fstream>

using namespace std;

Chart::Chart() {
    difficulty = "N/A";
}

Chart::Chart(const string& filename, const string difficulty) {
    ifstream fin(filename);
    json data = json::parse(fin);

    for (auto& note : data["notes"][difficulty]) {
        int d = note["d"];

        Direction temp_dir;

        switch (d) {
            case 0:temp_dir = Direction::LEFT;
                break;
            case 1:temp_dir = Direction::DOWN;
                break;
            case 2:temp_dir = Direction::UP;
                break;
            case 3:temp_dir = Direction::RIGHT;
                break;
            case 4:temp_dir = Direction::LEFT;
                break;
            case 5:temp_dir = Direction::DOWN;
                break;
            case 6:temp_dir = Direction::UP;
                break;
            case 7:temp_dir = Direction::RIGHT;
                break;

        }

        float duration = note.contains("l") ? note["l"].get<float>() : 0.f;
        float time = note["t"].get<float>();

        if (d <= 3)
            player_notes.push_back({time, temp_dir, duration});
        else
            opponent_notes.push_back({time, temp_dir, duration});
    }

    this->difficulty = difficulty;
}

vector<Note> Chart::getPlayerNotes() const {
    return player_notes;
}

vector<Note> Chart::getOpponentNotes() const {
    return opponent_notes;
}

