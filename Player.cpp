#include "Player.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

Player::Player(sf::Texture& texture) : sprite(texture){

    sprite.setScale({0.45f, 0.45f});

    idleFrames = {
        sf::IntRect({10, 10}, {390, 390}),
        sf::IntRect({400, 10}, {390, 390}),
        sf::IntRect({810, 10}, {390, 390})
    };

    missFrames = {
        sf::IntRect({10, 410}, {390, 390})
    };

    hitFrames = {
        sf::IntRect({1230, 10}, {370, 380})
    };

    sprite.setTextureRect(idleFrames[0]);
    sprite.setPosition({900.f, 400.f});
}

void Player::setState(PlayerState new_state) {
    if (curr_state != new_state) {
        curr_state = new_state;
        frameTimer = 0;

        if (curr_state == PlayerState::IDLE) sprite.setTextureRect(idleFrames[0]);
        else if (curr_state == PlayerState::HIT) sprite.setTextureRect(hitFrames[0]);
        else if (curr_state == PlayerState::MISS) sprite.setTextureRect(missFrames[0]);
    }
}

void Player::update(float dt) {
    frameTimer += dt;

    vector<sf::IntRect> *activeFrames = &idleFrames;
    if (curr_state == PlayerState::HIT) activeFrames = &hitFrames;
    else if (curr_state == PlayerState::MISS) activeFrames = &missFrames;

    if (frameTimer >= frameDuration) {
        frameTimer = 0.f;
        curr_frame++;

        if (curr_frame >= activeFrames->size()) {
            // if (curr_state == PlayerState::IDLE)
            //     curr_frame = 0;
            // else {
            //     curr_state = PlayerState::IDLE;
            //     curr_frame = 0;
            //     activeFrames = &idleFrames;
            // }
            curr_frame = 0;
        }

        sprite.setTextureRect((*activeFrames)[curr_frame]);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}