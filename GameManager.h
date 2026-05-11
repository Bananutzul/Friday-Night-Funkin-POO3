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
    GameManager() {}
    static GameManager* instance;
    vector<unique_ptr<Arrow>> player_arrows;
    vector<unique_ptr<HoldArrow>> player_holdarrows;
    vector<unique_ptr<Arrow>> opponent_arrows;
    vector<unique_ptr<HoldArrow>> opponent_holdarrows;
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
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void loadSong(unique_ptr<Song> song);
    void spawnNotes();

    int getScore() const;
    int getCombo() const;
    map<string, sf::Texture> getTexture() const;

    void preloadTextures();
    void loadTargetZones();
    void drawTargetZones(sf::RenderWindow& window);

    template<typename T>
    void updateNotes(vector<unique_ptr<T>>& notes, float dt) {
        for (auto& note : notes)
            note->update(dt);
    }

    template<typename T>
    void drawNotes(vector<unique_ptr<T>>& notes, sf::RenderWindow& window) {
        for (auto& note : notes)
            note->draw(window);
    }

    template<typename T, typename Lambda>
    void eraseNotes(vector<unique_ptr<T>>& notes, Lambda lambda) {
        notes.erase(remove_if(notes.begin(), notes.end(),
            lambda), notes.end());
    }

    void addNote(unique_ptr<Arrow> note);
    void addNote(unique_ptr<HoldArrow> note);
};