#pragma once

#include <iostream>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Arrow.h"
#include "HoldArrow.h"

using namespace std;

class GameManager{
private:
    GameManager() {
        targetZones[0] = Arrow({100.f, 0.f}, 0.f, Direction::LEFT, false);
        targetZones[1] = Arrow({250.f, 0.f}, 0.f, Direction::DOWN, false);
        targetZones[2] = Arrow({400.f, 0.f}, 0.f, Direction::UP, false);
        targetZones[3] = Arrow({550.f, 0.f}, 0.f, Direction::RIGHT, false);
    }
    static GameManager* instance;
    vector<unique_ptr<Arrow>> arrows;
    Arrow targetZones[4];
    int score;
    int combo;
public:
    static GameManager* getInstance() {
        if (instance == nullptr)
            instance = new GameManager();
        return instance;
    }

    void handleInput(sf::Event event); // pt note normale
    void handleHeldInput(); // pt note de tipul hold
    bool checkHit(Direction dir);
    void checkHold(Direction dir);
    void addNote(unique_ptr<Arrow> note);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};