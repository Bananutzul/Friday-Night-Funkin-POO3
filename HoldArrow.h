#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "Arrow.h"

class HoldArrow : public Arrow {
private:
    float duration;
    bool isHeld;
public:
    HoldArrow();
    HoldArrow(sf::Vector2f, float, Direction, bool, float, bool);
    HoldArrow(const HoldArrow& obj);
    HoldArrow& operator=(const HoldArrow& obj);
    virtual ~HoldArrow();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};