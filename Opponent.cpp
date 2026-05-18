#include "Opponent.h"

Opp::Opp(sf::Texture& texture) : sprite(texture) {
    curr_state = Opp_State::IDLE;

    sprite.setScale({0.45f, 0.45f});

    idleFrames = {
        sf::IntRect({30, 200}, {440, 780}),
        sf::IntRect({473, 200}, {438, 780}),
        sf::IntRect({916, 200}, {438, 780})
    };

    hitFrames = {sf::IntRect({80, 1250}, {430, 780})};

    sprite.setTextureRect(idleFrames[0]);
    sprite.setPosition({250.f, 250.f});
}

void Opp::setState(Opp_State new_state) {
    if (new_state != curr_state) {
        curr_state = new_state;
        curr_frame = 0;
        frameTimer = 0;

        if (curr_state == Opp_State::IDLE)
            sprite.setTextureRect(idleFrames[0]);
        else
            sprite.setTextureRect(hitFrames[0]);
    }
}

void Opp::update(float dt) {
    frameTimer += dt;

    vector<sf::IntRect>* activeFrames = &idleFrames;
    if (curr_state == Opp_State::HIT)
        activeFrames = &hitFrames;

    if (frameTimer >= frameDuration) {
        frameTimer = 0.f;
        curr_frame++;

        if (curr_frame >= activeFrames->size()) {
            if (curr_state == Opp_State::IDLE) {
                curr_frame = 0;
            }else {
                curr_frame = 0;
                curr_state = Opp_State::IDLE;
                activeFrames = &idleFrames;
            }
        }

        sprite.setTextureRect((*activeFrames)[curr_frame]);
    }
}

void Opp::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
