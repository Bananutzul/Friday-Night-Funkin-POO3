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
        targetZones[0] = Arrow({700.f, 0.f}, 0.f, Direction::LEFT, false, false, textures["arrows"]);
        targetZones[1] = Arrow({840.f, 0.f}, 0.f, Direction::DOWN, false, false, textures["arrows"]);
        targetZones[2] = Arrow({980.f, 0.f}, 0.f, Direction::UP, false, false, textures["arrows"]);
        targetZones[3] = Arrow({1120.f, 0.f}, 0.f, Direction::RIGHT, false, false, textures["arrows"]);
        targetZones[4] = Arrow({100.f, 0.f}, 0.f, Direction::LEFT, false, false, textures["arrows"]);
        targetZones[5] = Arrow({240.f, 0.f}, 0.f, Direction::DOWN, false, false, textures["arrows"]);
        targetZones[6] = Arrow({380.f, 0.f}, 0.f, Direction::UP, false, false, textures["arrows"]);
        targetZones[7] = Arrow({520.f, 0.f}, 0.f, Direction::RIGHT, false, false, textures["arrows"]);
    }
    static GameManager* instance;
    vector<unique_ptr<Arrow>> arrows;
    Arrow targetZones[8];
    int score = 0;
    int combo = 0;
    float travelTime = 550 / 200.f * 1000.f;

    vector<Note> playerNotes;
    vector<Note> opponentNotes;
    unique_ptr<Song> curr_song;
    int nextPlayerNote = 0, nextOpponentNote = 0; // indexi prin care tinem minte urmatoarea nota pe care trebuie sa o afisam

    map<string, sf::Texture> textures; // preload la texturi
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
    void spawnNotes();

    int getScore() const;
    int getCombo() const;
    map<string, sf::Texture> getTexture() const;

    void preloadTextures();
};