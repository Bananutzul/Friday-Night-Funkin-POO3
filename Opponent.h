#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

enum class Opp_State {IDLE, HIT};

class Opp {
private:
    sf::Sprite sprite;
    vector<sf::IntRect> idleFrames;
    vector<sf::IntRect> hitFrames;

    float frameDuration = 0.16f;
    float frameTimer = 0.f;
    int curr_frame = 0;
    Opp_State curr_state;
public:
    Opp(sf::Texture& texture);

    void setState(Opp_State new_state);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};