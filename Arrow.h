#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"

enum class Direction { LEFT, DOWN, UP, RIGHT};
enum class targetState {IDLE, PRESSED, HIT}; // enum pentru a tine minte starile pt target zones ca sa schimbam culoarea cand sunt apasate

class Arrow : public GameObject{
protected:
    sf::Vector2f position;
    float speed;
    sf::Texture texture;
    sf::Sprite sprite{texture};
    Direction direction;
    bool isPressed;
    bool isPlayerNote;

    bool isVisible = true;

    targetState current_state = targetState::IDLE;
    sf::IntRect idleRect; // sprite sheet cutout-ul pt target zone idle (adica cand sunt gri)

    void initShape(const sf::Texture& texture);
public:
    Arrow();
    Arrow(sf::Vector2f, float, Direction, bool, bool, const sf::Texture&);
    Arrow(const Arrow& obj);
    Arrow& operator=(const Arrow& obj);
    virtual ~Arrow();

    // animatii pt target zones
    void setState(targetState new_state);
    void updateTarget(float dt);
    targetState getState();

    sf::Sprite& getSprite();

    bool isOffScreen();
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    void setIsVisible(bool val);
    bool getIsVisible() const;

    Direction getDirection() const;
    sf::Vector2f getPosition() const;
    void setIsPressed(bool val);
    bool getIsPressed() const;
    bool getIsPlayerNote() const;
    float getX() const;
};