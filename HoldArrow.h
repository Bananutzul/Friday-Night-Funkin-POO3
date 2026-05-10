#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "Arrow.h"

using namespace std;

class HoldArrow : public Arrow {
private:
    sf::Vector2f line_position = position;
    float duration;
    bool isHeld;
    bool miss = false;
    float current_time_held = 0.f;
    float tileHeight = 20.f;
    sf::Texture line_texture;
    sf::Sprite line_sprite{line_texture}; // e nevoie de line_texture ca sa initializam line_sprite cu ceva
    vector<sf::Sprite> lineTiles;
public:
    HoldArrow();
    HoldArrow(sf::Vector2f, float, Direction, bool, bool, float, bool);
    HoldArrow(const HoldArrow& obj);
    HoldArrow& operator=(const HoldArrow& obj);
    virtual ~HoldArrow();

    bool isFinished();
    void update(float dt) override;
    void updateLine(float dt);
    void draw(sf::RenderWindow& window) override;
    void initLine();
    void setIsHeld(bool val);
    bool isMiss() const;
    void setMiss(bool val);
    bool getIsHeld() const;
    void updateHeldTimer(float dt);
};