#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"

enum class Direction { LEFT, DOWN, UP, RIGHT};

class Arrow : public GameObject{
protected:
    sf::Vector2f position;
    float speed;
    sf::Texture texture;
    sf::Sprite sprite{texture};
    Direction direction;
    bool isPressed;
    bool isPlayerNote;

    void initShape(const sf::Texture& texture);
public:
    Arrow();
    Arrow(sf::Vector2f, float, Direction, bool, bool, const sf::Texture&);
    Arrow(const Arrow& obj);
    Arrow& operator=(const Arrow& obj);
    virtual ~Arrow();

    bool isOffScreen();
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    Direction getDirection() const;
    sf::Vector2f getPosition() const;
    void setIsPressed(bool val);
    bool getIsPressed() const;
    bool getIsPlayerNote() const;
    float getX() const;
};