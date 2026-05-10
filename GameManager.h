#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Arrow.h"
#include "Chart.h"
#include "Song.h"
#include "HoldArrow.h"

using namespace std;

class GameManager{
private:
    GameManager() {
        targetZones[0] = Arrow({650.f, 0.f}, 0.f, Direction::LEFT, false, false);
        targetZones[1] = Arrow({800.f, 0.f}, 0.f, Direction::DOWN, false, false);
        targetZones[2] = Arrow({950.f, 0.f}, 0.f, Direction::UP, false, false);
        targetZones[3] = Arrow({1100.f, 0.f}, 0.f, Direction::RIGHT, false, false);
    }
    static GameManager* instance;
    vector<unique_ptr<Arrow>> arrows;
    Arrow targetZones[4];
    int score = 0;
    int combo = 0;
    float travelTime = 550 / 1.6 * 1000.f;

    vector<Note> playerNotes;
    vector<Note> opponentNotes;
    unique_ptr<Song> curr_song;
    int nextPlayerNote = 0, nextOpponentNote = 0; // indexi prin care tinem minte urmatoarea nota pe care trebuie sa o afisam
public:
    static GameManager* getInstance() {
        if (instance == nullptr)
            instance = new GameManager();
        return instance;
    }

    void handleInput(sf::Event event); // pt note normale
    void handleHeldInput(); // pt note de tipul hold
    void checkHit(Direction dir);
    void checkHold(Direction dir);
    void releaseHold(Direction dir);
    void addNote(unique_ptr<Arrow> note);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void loadSong(unique_ptr<Song> song);

    int getScore() const;
    int getCombo() const;
};