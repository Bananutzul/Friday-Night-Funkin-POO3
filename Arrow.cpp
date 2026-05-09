#include "Arrow.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

void Arrow::initShape() {
    shape.setPosition({position.x, position.y});
    tip.setPointCount(3);

    switch(direction) {
        case Direction::LEFT:
            shape.setSize({25.f, 15.f});
            this->shape.setFillColor(sf::Color::Red);
            tip.setPoint(0, {0.f, 7.5f});
            tip.setPoint(1, {20.f, -5.f});
            tip.setPoint(2, {20.f, 20.f});
            tip.setFillColor(sf::Color::Red);
            break;
        case Direction::DOWN:
            shape.setSize({15.f, 25.f});
            this->shape.setFillColor(sf::Color::Blue);
            tip.setPoint(0, {-5.f, 0.f});
            tip.setPoint(1, {20.f, 0.f});
            tip.setPoint(2, {7.5f, 35.f});
            tip.setFillColor(sf::Color::Blue);
            break;
        case Direction::UP:
            shape.setSize({15.f, 25.f});
            this->shape.setFillColor(sf::Color::Green);
            tip.setPoint(0, {7.5f, 0.f});
            tip.setPoint(1, {-5.f, 35.f});
            tip.setPoint(2, {20.f, 35.f});
            tip.setFillColor(sf::Color::Green);
            break;
        case Direction::RIGHT:
            shape.setSize({25.f, 15.f});
            this->shape.setFillColor(sf::Color(255, 105, 180)); // roz
            tip.setPoint(0, {20.f, 7.5f});
            tip.setPoint(1, {0.f, -5.f});
            tip.setPoint(2, {0.f, 20.f});
            tip.setFillColor(sf::Color(255, 105, 180));
            break;
    }
}

Arrow::Arrow() {
    position.x = 0;
    position.y = 0;

    speed = 0;

    direction = Direction::DOWN;

    isPressed = false;

    initShape();
}

Arrow::Arrow(sf::Vector2f position, float speed, sf::RectangleShape shape, Direction direction, bool isPressed) {
    this->position = position;
    this->speed = speed;
    this->direction = direction;
    this->isPressed = isPressed;
    this->initShape();
}

Arrow::Arrow(const Arrow& obj) {
    position = obj.position;
    speed = obj.speed;
    direction = obj.direction;
    isPressed = obj.isPressed;
    initShape();
}

Arrow& Arrow::operator=(const Arrow& obj) {
    if (this == &obj)
        return *this;

    position = obj.position;
    speed = obj.speed;
    direction = obj.direction;
    isPressed = obj.isPressed;
    initShape();

    return *this;
}

Arrow::~Arrow() {}

void Arrow::update(float dt) {
    position.y += speed * dt;
    shape.setPosition({position.x, position.y});

    switch (direction) {
        case Direction::UP:
            tip.setPosition({position.x, position.y - 45.f});
            break;
        case Direction::DOWN:
            tip.setPosition({position.x, position.y + 35.f});
            break;
        case Direction::LEFT:
            tip.setPosition({position.x - 25.f, position.y});
            break;
        case Direction::RIGHT:
            tip.setPosition({position.x + 30.f, position.y});
            break;
    }
}

void Arrow::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(tip);
}