#include "Arrow.h"
#include "HoldArrow.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

void Arrow::initShape(const sf::Texture& texture) {
        sprite = sf::Sprite(texture);

        switch(direction) {
            case Direction::LEFT:
                sprite.setTextureRect(sf::IntRect({480, 10}, {140, 150}));
                break;
            case Direction::DOWN:
                sprite.setTextureRect(sf::IntRect({1470, 10}, {140, 150}));
                break;
            case Direction::UP:
                sprite.setTextureRect(sf::IntRect({490, 993}, {145, 150}));
                break;
            case Direction::RIGHT:
                sprite.setTextureRect(sf::IntRect({1460, 998}, {140, 150}));
                break;
        }

        sprite.setPosition(position);
    }

Arrow::Arrow() {
    position.x = 0;
    position.y = 0;

    speed = 0;

    direction = Direction::DOWN;

    isPressed = false;
    isPlayerNote = false;

    initShape(texture);
}

Arrow::Arrow(sf::Vector2f position, float speed, Direction direction, bool isPressed, bool isPlayer, const sf::Texture& texture) {
    this->position = position;
    this->speed = speed;
    this->direction = direction;
    this->isPressed = isPressed;
    isPlayerNote = isPlayer;
    this->texture = texture;
    this->initShape(texture);
}

Arrow::Arrow(const Arrow& obj) {
    position = obj.position;
    speed = obj.speed;
    direction = obj.direction;
    isPressed = obj.isPressed;
    isPlayerNote = obj.isPlayerNote;
    texture = obj.texture;
    initShape(texture);
}

Arrow& Arrow::operator=(const Arrow& obj) {
    if (this == &obj)
        return *this;

    position = obj.position;
    speed = obj.speed;
    direction = obj.direction;
    isPressed = obj.isPressed;
    isPlayerNote = obj.isPlayerNote;
    texture = obj.texture;
    initShape(texture);

    return *this;
}

Arrow::~Arrow() {}

bool Arrow::isOffScreen() {
    if (isPlayerNote == false && dynamic_cast<HoldArrow*>(this) == nullptr)
        return position.y <= 0.f;
    return position.y < -50.f;
}

void Arrow::update(float dt) {
    position.y -= speed * dt;
    sprite.setPosition(position);
}

void Arrow::draw(sf::RenderWindow& window) {
    sprite.setScale({0.5f, 0.5f});
    window.draw(sprite);
}

Direction Arrow::getDirection() const {
    return direction;
}

sf::Vector2f Arrow::getPosition() const {
    return position;
}

void Arrow::setIsPressed(bool val) {
    isPressed = val;
}

bool Arrow::getIsPressed() const {
    return isPressed;
}

bool Arrow::getIsPlayerNote() const {
    return isPlayerNote;
}

float Arrow::getX() const {
    return position.x;
}



