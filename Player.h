#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

using namespace std;

enum class PlayerState {IDLE, HIT, MISS}; // enum cu starile player-ului

class Player {
private:
    sf::Sprite sprite;
    vector<sf::IntRect> idleFrames;
    vector<sf::IntRect> missFrames;
    vector<sf::IntRect> hitFrames;

    int curr_frame = 0;
    float frameTimer = 0.f;
    float frameDuration = 0.08f;
    PlayerState curr_state = PlayerState::IDLE;

public:
    Player(sf::Texture& texture);

    void setState(PlayerState new_state);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};