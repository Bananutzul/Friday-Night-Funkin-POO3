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
    float duration;
    bool isHeld;
    float tileHeight = 20.f;
    sf::Texture line_texture;
    sf::Sprite line_sprite{line_texture}; // e nevoie de line_texture ca sa initializam line_sprite cu ceva
    vector<sf::Sprite> lineTiles;
public:
    HoldArrow();
    HoldArrow(sf::Vector2f, float, Direction, bool, float, bool);
    HoldArrow(const HoldArrow& obj);
    HoldArrow& operator=(const HoldArrow& obj);
    virtual ~HoldArrow();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void initLine();
    void setIsHeld(bool val);
};