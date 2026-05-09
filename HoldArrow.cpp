#pragma once

#include "HoldArrow.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

// void HoldArrow::initLine() {
//     line_texture.loadFromFile("arrows.png");
//     line_sprite = sf::Sprite(line_texture);
//
//     switch(direction) {
//         case Direction::LEFT:
//             line_sprite.setTextureRect(sf::IntRect({670, 50}, {50, 50}));
//             break;
//         case Direction::DOWN:
//             line_sprite.setTextureRect(sf::IntRect({1650, 50}, {50, 50}));
//             break;
//         case Direction::UP:
//             line_sprite.setTextureRect(sf::IntRect({670, 943}, {50, 50}));
//             break;
//         case Direction::RIGHT:
//             line_sprite.setTextureRect(sf::IntRect({1650, 943}, {50, 50}));
//             break;
//     }
//
//     line_sprite.setPosition({position.x, position.y + 40.f});
// }

void HoldArrow::initLine() {
    line_texture.loadFromFile("arrows.png");

    float tileHeight = 25.f;
    int numTiles = (duration * speed) / tileHeight;

    for (int i = 0; i < numTiles; i++) {
        sf::Sprite tile(line_texture);

        switch(direction) {
            case Direction::LEFT:
                tile.setTextureRect(sf::IntRect({640, 10}, {36, 45}));
                break;
            case Direction::DOWN:
                tile.setTextureRect(sf::IntRect({1639, 10}, {36, 45}));
                break;
            case Direction::UP:
                tile.setTextureRect(sf::IntRect({658, 995}, {36, 45}));
                break;
            case Direction::RIGHT:
                tile.setTextureRect(sf::IntRect({1629, 1000}, {36, 45}));
                break;
        }

        tile.setScale({0.5f, 0.5f});
        tile.setPosition({position.x, position.y + 40.f + i * tileHeight});
        lineTiles.push_back(tile);
    }
}

HoldArrow::HoldArrow() : Arrow(){
    duration = 0;
    isHeld = false;
    initLine();
}

HoldArrow::HoldArrow(sf::Vector2f position, float speed,
    Direction direction, bool isPressed, float duration, bool isHeld) : Arrow(position, speed, direction, isPressed){

    this->duration = duration;
    this->isHeld = isHeld;
    initLine();
}

HoldArrow::HoldArrow(const HoldArrow &obj) : Arrow(obj){
    duration = obj.duration;
    isHeld = obj.isHeld;
    initLine();
}

HoldArrow::~HoldArrow(){};

void HoldArrow::update(float dt) {
    position.y -= speed * dt;
    for (int i = 0; i < lineTiles.size(); i++) {
        lineTiles[i].setPosition({position.x + 28.f, position.y + 40.f + i * tileHeight});
    }
    sprite.setPosition(position);
}

void HoldArrow::draw(sf::RenderWindow& window) {
    for (auto& tile : lineTiles)
        window.draw(tile);
    sprite.setScale({0.5f, 0.5f});
    window.draw(sprite);
}

