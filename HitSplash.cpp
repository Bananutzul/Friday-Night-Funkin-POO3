#include "HitSplash.h"

HitSplash::HitSplash(sf::Vector2f position, sf::Texture &texture, Direction &dir) : sprite(texture){
    curr_frame = 0;
    timer = 0.f;
    frame_duration = 0.045f;
    finished = false;

    switch (dir) {
        case Direction::LEFT:
            frames.push_back(sf::IntRect({7, 725}, {180, 200}));
            frames.push_back(sf::IntRect({200, 715}, {230, 250}));
            frames.push_back(sf::IntRect({438, 715}, {276, 270}));
            frames.push_back(sf::IntRect({722, 715}, {235, 270}));
            break;
        case Direction::DOWN:
            frames.push_back(sf::IntRect({993, 725}, {180, 200}));
            frames.push_back(sf::IntRect({1185, 715}, {230, 250}));
            frames.push_back(sf::IntRect({1425, 715}, {276, 270}));
            frames.push_back(sf::IntRect({1708, 715}, {235, 270}));
            break;
        case Direction::UP:
            frames.push_back(sf::IntRect({7, 1708}, {180, 200}));
            frames.push_back(sf::IntRect({200, 1699}, {230, 250}));
            frames.push_back(sf::IntRect({438, 1699}, {276, 270}));
            frames.push_back(sf::IntRect({722, 1699}, {235, 270}));
            break;
        case Direction::RIGHT:
            frames.push_back(sf::IntRect({993, 1699}, {180, 200}));
            frames.push_back(sf::IntRect({1185, 1699}, {230, 250}));
            frames.push_back(sf::IntRect({1425, 1699}, {276, 270}));
            frames.push_back(sf::IntRect({1708, 1699}, {230, 270}));
            break;
    }

    if (!frames.empty()) {
        sprite.setTextureRect(frames[0]);

        float center_x = frames[0].size.x / 2.f;
        float center_y = frames[0].size.y / 2.f;
        sprite.setOrigin({center_x, center_y}); // setam centrul pt animatie ca sa nu sara (sprite-urile au diferite marimi)
    }

    sprite.setPosition({position.x + 15.f, position.y + 15.f});
    sprite.setScale({0.4f, 0.4f});
}

void HitSplash::update(float dt) {
    if (finished)
        return;

    timer += dt;

    if (timer >= frame_duration) {
        timer = 0.f;
        curr_frame++;

        if (curr_frame < frames.size()) {
            sprite.setTextureRect(frames[curr_frame]);
        }else
            finished = true;
    }
}

void HitSplash::draw(sf::RenderWindow& window) {
    if (!finished)
        window.draw(sprite);
}

bool HitSplash::isFinished() {
    return finished;
}
