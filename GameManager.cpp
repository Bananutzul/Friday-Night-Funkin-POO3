#include "GameManager.h"
#include <cmath>
#include <iostream>
#include <memory>

using namespace std;

GameManager* GameManager::instance = nullptr;

void GameManager::checkHit(Direction dir) {
    for (auto& note : arrows) {
        if (note->getIsPlayerNote()) {
            if (note->getDirection() == dir && note->getX() ) {
                float noteY, targetY, offset;

                noteY = note->getPosition().y;
                targetY = targetZones[(int)dir].getPosition().y;
                offset = abs(noteY - targetY);

                if (offset <= 100.f) {
                    note->setIsPressed(true);

                    if (offset <= 50.f) {
                        score += 100;
                        combo++;
                    }else
                        combo = 0;
                }
                break;
            }
        }
    }

}

void GameManager::checkHold(Direction dir) {
    for (auto& note : holdarrows) {

        if (note->getDirection() == dir && note->getIsPlayerNote()) {
            float noteY, targetY, offset;

            noteY = note->getPosition().y;
            targetY = targetZones[(int)dir].getPosition().y;

            offset = abs(noteY - targetY);

            if (offset <= 50.f) {
                note->setIsHeld(true);
                score += 50;
                combo++;
            }else {
                note->setMiss(true);
            }
        }
    }
}

void GameManager::handleHeldInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        checkHold(Direction::LEFT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        checkHold(Direction::DOWN);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        checkHold(Direction::RIGHT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        checkHold(Direction::UP);
}

void GameManager::handleInput(sf::Event event) {
    if (const auto& keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        Direction dir;
        bool valid = true;

        switch (keyEvent->code) {
            case sf::Keyboard::Key::A :
                dir = Direction::LEFT;
                break;
            case sf::Keyboard::Key::S :
                dir = Direction::DOWN;
                break;
            case sf::Keyboard::Key::D :
                dir = Direction::RIGHT;
                break;
            case sf::Keyboard::Key::W :
                dir = Direction::UP;
                break;
            default:
                valid = false;
                break;
        }

        if (valid){

            bool isHoldNote = false;

            for (auto& hold : holdarrows) {
                if (hold->getIsPlayerNote()) {
                    if (hold->getDirection() == dir) {
                        isHoldNote = true;
                        break;
                    }
                }
            }

        if (!isHoldNote)
            checkHit(dir);
        }
    }

    if (const auto& keyEvent = event.getIf<sf::Event::KeyReleased>()) {
        Direction dir;
        bool valid = true;

        switch (keyEvent->code) {
            case sf::Keyboard::Key::A:
                dir = Direction::LEFT;
                break;
            case sf::Keyboard::Key::S:
                dir = Direction::DOWN;
                break;
            case sf::Keyboard::Key::W:
                dir = Direction::UP;
                break;
            case sf::Keyboard::Key::D:
                dir = Direction::RIGHT;
                break;
            default:
                valid = false;
                break;
        }

        if (valid) {
            releaseHold(dir);
            combo = 0;
        }
    }
}

void GameManager::releaseHold(Direction dir) {
    for (auto& hold : holdarrows) {
        if (hold->getDirection() == dir && hold->getIsPlayerNote())
            hold->setIsHeld(false);
    }
}

void GameManager::update(float dt) {
    handleHeldInput();

    updateNotes(arrows, dt);
    updateNotes(holdarrows, dt);

    eraseNotes(arrows, [](const unique_ptr<Arrow>& note) {
        return note->isOffScreen() || note->getIsPressed();
    });

    eraseNotes(holdarrows, [](const unique_ptr<HoldArrow>& note) {
    return note->isMiss() || note->isFinished();
});
}

void GameManager::draw(sf::RenderWindow& window) {
    for (auto& note : arrows)
        note->draw(window);
    for (auto& hold : holdarrows)
        hold->draw(window);
}

int GameManager::getScore() const {
    return score;
}

int GameManager::getCombo() const {
    return combo;
}

void GameManager::loadSong(unique_ptr<Song> song) {
    curr_song = std::move(song);

    playerNotes = curr_song->getChart().getPlayerNotes();
    opponentNotes = curr_song->getChart().getOpponentNotes();

    nextPlayerNote = 0;
    nextOpponentNote = 0;

    arrows.clear();
    holdarrows.clear();

    score = 0;
    combo = 0;

    curr_song->play();
}

void GameManager::spawnNotes() {
    float current_timeMs = curr_song->getTimeMs();
    travelTime = 550.f / 200.f * 1000.f;

    while (nextPlayerNote < playerNotes.size()) {
        auto& note = playerNotes[nextPlayerNote];

        if (current_timeMs >= note.time - travelTime) {
            cout << "Spawn Note Now" << travelTime << endl;

            float x;

            switch (note.direction) {
                case Direction::LEFT: x = 700.f;break;
                case Direction::DOWN: x = 840.f;break;
                case Direction::UP: x = 980.f;break;
                case Direction::RIGHT: x = 1120.f;break;
            }

            if (note.duration > 0) {
                holdarrows.push_back(make_unique<HoldArrow>(sf::Vector2f({x, 600.f}), 200.f, note.direction, false, textures["arrows"], true, note.duration / 1000.f, false));
            }else {
                arrows.push_back(make_unique<Arrow>(sf::Vector2f({x, 600.f}), 200.f, note.direction, false, true, textures["arrows"]));
            }

            nextPlayerNote++;
        }else break;
    }

    while (nextOpponentNote < opponentNotes.size()) {
        auto& note = opponentNotes[nextOpponentNote];

        if (current_timeMs >= note.time - travelTime) {
            cout << "Spawn Note Now" << travelTime << endl;

            float x;

            switch (note.direction) {
                case Direction::LEFT: x = 100.f;break;
                case Direction::DOWN: x = 240.f;break;
                case Direction::UP: x = 380.f;break;
                case Direction::RIGHT: x = 520.f;break;
            }

            if (note.duration > 0) {
                holdarrows.push_back(make_unique<HoldArrow>(sf::Vector2f({x, 600.f}), 200.f, note.direction, false, textures["arrows"], false, note.duration / 1000.f, false));
            }else {
                arrows.push_back(make_unique<Arrow>(sf::Vector2f({x, 600.f}), 200.f, note.direction, false, false, textures["arrows"]));
            }

            nextOpponentNote++;
        }else break;
    }
}

void GameManager::preloadTextures() {
    sf::Texture texture;
    texture.loadFromFile("arrows.png");
    textures["arrows"] = std::move(texture);
}

map<string, sf::Texture> GameManager::getTexture() const {
    return textures;
}

void GameManager::loadTargetZones() {
    targetZones[0] = Arrow({700.f, 0.f}, 0.f, Direction::LEFT, false, false, textures["arrows"]);
    targetZones[1] = Arrow({840.f, 0.f}, 0.f, Direction::DOWN, false, false, textures["arrows"]);
    targetZones[2] = Arrow({980.f, 0.f}, 0.f, Direction::UP, false, false, textures["arrows"]);
    targetZones[3] = Arrow({1120.f, 0.f}, 0.f, Direction::RIGHT, false, false, textures["arrows"]);
    targetZones[4] = Arrow({100.f, 0.f}, 0.f, Direction::LEFT, false, false, textures["arrows"]);
    targetZones[5] = Arrow({240.f, 0.f}, 0.f, Direction::DOWN, false, false, textures["arrows"]);
    targetZones[6] = Arrow({380.f, 0.f}, 0.f, Direction::UP, false, false, textures["arrows"]);
    targetZones[7] = Arrow({520.f, 0.f}, 0.f, Direction::RIGHT, false, false, textures["arrows"]);
}

void GameManager::drawTargetZones(sf::RenderWindow &window) {
    for (auto& note : targetZones)
        note.draw(window);
}

