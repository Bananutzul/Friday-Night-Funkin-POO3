#include "Arrow.h"
#include "HoldArrow.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

void Arrow::initShape(const sf::Texture& texture) {
    sprite = sf::Sprite(texture);

    if (this->speed == 0.f) {
        switch(direction) {
            case Direction::LEFT:
                idleRect = sf::IntRect({310, 10}, {150, 155});
                sprite.setTextureRect(idleRect);
                break;
            case Direction::DOWN:
                idleRect = sf::IntRect({1303, 8}, {150, 155});
                sprite.setTextureRect(idleRect);
                break;
            case Direction::UP:
                idleRect = sf::IntRect({320, 993}, {155, 150});
                sprite.setTextureRect(idleRect);
                break;
            case Direction::RIGHT:
                idleRect = sf::IntRect({1300, 998}, {150, 150});
                sprite.setTextureRect(idleRect);
                break;
        }
    }else {
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
    if (sprite.getScale() == sf::Vector2f({1.f, 1.f}))
        sprite.setScale({0.40f, 0.40f});
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

// Animatii pt target zones

sf::Sprite &Arrow::getSprite() {
    return sprite;
}

void Arrow::setState(targetState new_state) {
    if (current_state == targetState::HIT && new_state == targetState::PRESSED)
        return; // daca e deja in animatie nota, nu mai lasam sa o schimbe pressed, pt ca ar strica animatia / ar fi intrerupta

    current_state = new_state;

    if (current_state == targetState::IDLE) {
        sprite.setTextureRect(idleRect);
        sprite.setScale({0.4f, 0.4f});
    }
    else if (current_state == targetState::PRESSED) {
        switch (direction) {
            case Direction::LEFT:
                sprite.setTextureRect(sf::IntRect({155, 10}, {140, 140}));
                break;
            case Direction::DOWN:
                sprite.setTextureRect(sf::IntRect({1148, 10}, {140, 140}));
                break;
            case Direction::UP:
                sprite.setTextureRect(sf::IntRect({160, 993}, {145, 140}));
                break;
            case Direction::RIGHT:
                sprite.setTextureRect(sf::IntRect({1148, 998}, {140, 140}));
                break;
        }
    }else if (current_state == targetState::HIT) {
        animationTimer = 0.f;

        switch (direction) {
            case Direction::LEFT:
                sprite.setTextureRect(sf::IntRect({240, 180}, {200, 200}));
                sprite.setScale({0.3f, 0.3f});
                break;
            case Direction::DOWN:
                sprite.setTextureRect(sf::IntRect({1240, 180}, {200, 200}));
                sprite.setScale({0.3f, 0.3f});
                break;
            case Direction::UP:
                sprite.setTextureRect(sf::IntRect({255, 1170}, {200, 200}));
                sprite.setScale({.3f, .3f});
                break;
            case Direction::RIGHT:
                sprite.setTextureRect(sf::IntRect({1220, 1170}, {200, 200}));
                sprite.setScale({.3f, .3f});
                break;
        }
    }
}

void Arrow::updateTarget(float dt) {
    if (current_state == targetState::HIT) {
        animationTimer += dt;

        if (animationTimer >= animationDuration) {
            current_state = targetState::IDLE;
            sprite.setTextureRect(idleRect);
        }
    }
}







