#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "Arrow.h"

using namespace std;

class HitSplash {
private:
    sf::Sprite sprite;
    vector<sf::IntRect> frames;
    int curr_frame;
    float timer;
    float frame_duration;
    bool finished;
public:
    HitSplash(sf::Vector2f position, sf::Texture& texture, Direction& dir);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};