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
#include "Player.h"
#include "HitSplash.h"

using namespace std;

class GameManager{
private:
    GameManager() {
        if (buf3.loadFromFile("intro3.ogg")) sound3 = new sf::Sound(buf3);
        if (buf2.loadFromFile("intro2.ogg")) sound2 = new sf::Sound(buf2);
        if (buf1.loadFromFile("intro1.ogg")) sound1 = new sf::Sound(buf1);
        if (bufGo.loadFromFile("introGo.ogg")) soundGo = new sf::Sound(bufGo);
    }
    static GameManager* instance;
    vector<unique_ptr<Arrow>> player_arrows;
    vector<unique_ptr<HoldArrow>> player_holdarrows;
    vector<unique_ptr<Arrow>> opponent_arrows;
    vector<unique_ptr<HoldArrow>> opponent_holdarrows;
    Arrow targetZones[8];
    int score = 0;
    string perfect;
    float travelTime = 550 / 200.f * 1000.f;
    int misses = 0;

    bool hasReleasedDir[4] = {true, true, true, true}; // buffer pt a rezolva problema de miss fals

    float gameTimeMs = 0.f;
    float introDurationMs = 0.f;
    bool songStarted = false;
    sf::SoundBuffer buf3, buf2, buf1, bufGo;
    sf::Sound* sound3 = nullptr, *sound2 = nullptr, *sound1 = nullptr, *soundGo = nullptr;
    bool played1 = false, played2 = false, played3 = false, playedGo = false;

    vector<Note> playerNotes;
    vector<Note> opponentNotes;
    unique_ptr<Song> curr_song;
    int nextPlayerNote = 0, nextOpponentNote = 0; // indexi prin care tinem minte urmatoarea nota pe care trebuie sa o afisam

    map<string, sf::Texture> textures; // preload la texturi

    sf::Texture playerTexture;
    unique_ptr<Player> player;

    sf::Texture backgroundTexture1;
    sf::Texture backgroundTexture2;
    unique_ptr<sf::Sprite> background1;
    unique_ptr<sf::Sprite> background2;

    vector<HitSplash> hitSplashes;
    sf::Texture splashTexture;
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
    string getPerfect() const;
    int getCombo() const;
    int getMisses() const;
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

    void spawnHitSplash(sf::Vector2f position, Direction dir);
};