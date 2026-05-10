
#include "HoldArrow.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

void HoldArrow::initLine() {
    line_texture.loadFromFile("arrows.png");

    float tileHeight = 25.f;
    int numTiles = (duration * speed) / tileHeight;

    for (int i = 0; i < numTiles; i++) {
        sf::Sprite tile(line_texture);

        switch(direction) {
            case Direction::LEFT:
                if (i != numTiles - 1)
                    tile.setTextureRect(sf::IntRect({640, 10}, {36, 45}));
                else
                    tile.setTextureRect(sf::IntRect({697, 10}, {36, 45}));
                break;
            case Direction::DOWN:
                if (i != numTiles - 1)
                    tile.setTextureRect(sf::IntRect({1639, 10}, {36, 45}));
                else
                    tile.setTextureRect(sf::IntRect({1692, 10}, {36, 45}));
                break;
            case Direction::UP:
                if (i != numTiles - 1)
                    tile.setTextureRect(sf::IntRect({658, 995}, {36, 45}));
                else
                    tile.setTextureRect(sf::IntRect({714, 995}, {36, 45}));
                break;
            case Direction::RIGHT:
                if (i != numTiles - 1)
                    tile.setTextureRect(sf::IntRect({1629, 1000}, {36, 45}));
                else
                    tile.setTextureRect(sf::IntRect({1682, 1000}, {36, 45}));
                break;
        }

        tile.setScale({0.5f, 0.5f});
        tile.setPosition({position.x, position.y + 40.f + i * tileHeight});
        lineTiles.push_back(tile);
    }
}

HoldArrow::HoldArrow() : Arrow(){
    line_position = position;
    duration = 0;
    isHeld = false;
    initLine();
}

HoldArrow::HoldArrow(sf::Vector2f position, float speed,
    Direction direction, bool isPressed, bool isPlayerNote, float duration, bool isHeld) : Arrow(position, speed, direction, isPressed, isPlayerNote){

    line_position = position;
    this->duration = duration;
    this->isHeld = isHeld;
    initLine();
}

HoldArrow::HoldArrow(const HoldArrow &obj) : Arrow(obj){
    line_position = position;
    duration = obj.duration;
    isHeld = obj.isHeld;
    initLine();
}

HoldArrow::~HoldArrow(){};

void HoldArrow::update(float dt) {
    if (!isHeld) {
        position.y -= speed * dt;
    }else {
        current_time_held += dt;
    }

    line_position.y -= speed * dt;

    sprite.setPosition(position);
    updateLine(dt);
}

void HoldArrow::updateLine(float dt) {
    for (int i = 0; i < lineTiles.size(); i++)
        lineTiles[i].setPosition({line_position.x + 28.f, line_position.y + 40.f + i * tileHeight});
}

void HoldArrow::draw(sf::RenderWindow& window) {
    for (auto& tile : lineTiles)
        window.draw(tile);
    sprite.setScale({0.5f, 0.5f});
    window.draw(sprite);
}

void HoldArrow::setIsHeld(bool val) {
    isHeld = val;
}

bool HoldArrow::isFinished() {
    return current_time_held >= duration;
}

bool HoldArrow::getIsHeld() const {
    return isHeld;
}

void HoldArrow::updateHeldTimer(float dt) {
    current_time_held += dt;
}

void HoldArrow::setMiss(bool val) {
    miss = val;
}

bool HoldArrow::isMiss() const {
    return miss;
}


