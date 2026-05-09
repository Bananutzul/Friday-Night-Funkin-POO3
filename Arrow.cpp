#include "Arrow.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

Arrow::Arrow() {
    position.x = 0;
    position.y = 0;

    speed = 0;

    shape.setSize({50.f, 50.f});
    shape.setPosition({position.x, position.y});
    direction = Direction::DOWN;

    switch(direction) {
        case Direction::LEFT:
            this->shape.setFillColor(sf::Color::Red);
            break;
        case Direction::DOWN:
            this->shape.setFillColor(sf::Color::Blue);
            break;
        case Direction::UP:
            this->shape.setFillColor(sf::Color::Green);
            break;
        case Direction::RIGHT:
            this->shape.setFillColor(sf::Color(255, 105, 180)); // roz
            break;
    }

    isPressed = false;
}

Arrow::Arrow(sf::Vector2f position, float speed, sf::RectangleShape shape, Direction direction, bool isPressed) {
    this->position = position;
    this->speed = speed;
    this->shape.setSize({50.f, 50.f});
    switch(direction) {
        case Direction::LEFT:
            this->shape.setFillColor(sf::Color::Red);
            break;
        case Direction::DOWN:
            this->shape.setFillColor(sf::Color::Blue);
            break;
        case Direction::UP:
            this->shape.setFillColor(sf::Color::Green);
            break;
        case Direction::RIGHT:
            this->shape.setFillColor(sf::Color(255, 105, 180)); // roz
            break;
    }
    this->shape.setPosition({position.x, position.y});
    this->direction = direction;
    this->isPressed = isPressed;
}

Arrow::Arrow(const Arrow& obj) {
    position = obj.position;
    speed = obj.speed;
    shape = obj.shape;
    direction = obj.direction;
    switch(direction) {
        case Direction::LEFT:
            this->shape.setFillColor(sf::Color::Red);
            break;
        case Direction::DOWN:
            this->shape.setFillColor(sf::Color::Blue);
            break;
        case Direction::UP:
            this->shape.setFillColor(sf::Color::Green);
            break;
        case Direction::RIGHT:
            this->shape.setFillColor(sf::Color(255, 105, 180)); // roz
            break;
    }
    isPressed = obj.isPressed;
}

Arrow& Arrow::operator=(const Arrow& obj) {
    if (this == &obj)
        return *this;

    position = obj.position;
    speed = obj.speed;
    shape = obj.shape;
    direction = obj.direction;
    switch(direction) {
        case Direction::LEFT:
            this->shape.setFillColor(sf::Color::Red);
            break;
        case Direction::DOWN:
            this->shape.setFillColor(sf::Color::Blue);
            break;
        case Direction::UP:
            this->shape.setFillColor(sf::Color::Green);
            break;
        case Direction::RIGHT:
            this->shape.setFillColor(sf::Color(255, 105, 180)); // roz
            break;
    }
    isPressed = obj.isPressed;

    return *this;
}

Arrow::~Arrow() {}

void Arrow::update(float dt) {
    position.y += speed * dt;
    shape.setPosition({position.x, position.y});
}

void Arrow::draw(sf::RenderWindow& window) {
    window.draw(shape);
}