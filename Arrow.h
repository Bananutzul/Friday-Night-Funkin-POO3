#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "GameObject/GameObject.h"

enum class Direction { LEFT, DOWN, UP, RIGHT};

class Arrow : public GameObject{
private:
    sf::Vector2f position;
    float speed;
    sf::RectangleShape shape; // tine minte culoarea si forma
    Direction direction;
    bool isPressed;
public:
    Arrow();
    Arrow(sf::Vector2f, float, sf::RectangleShape, Direction, bool);
    Arrow(const Arrow& obj);
    Arrow& operator=(const Arrow& obj);
    virtual ~Arrow();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};