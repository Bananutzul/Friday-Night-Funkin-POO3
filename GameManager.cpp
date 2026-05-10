#include "GameManager.h"
#include <cmath>
#include <iostream>

using namespace std;

bool GameManager::checkHit(Direction dir) {
    for (auto& note : arrows) {
        if (note->getDirection() == dir) {
            float noteY, targetY, offset;

            noteY = note->getPosition().y;
            targetY = targetZones[(int)dir].getPosition().y;
            offset = abs(noteY - targetY);

            if (offset <= 50.f) {
                note->setIsPressed(true);
                return true;
            }
        }
    }

    return false;
}

void GameManager::checkHold(Direction dir) {
    for (auto& note : arrows) {
        auto hold = dynamic_cast<HoldArrow*>(note.get());

        if (hold && hold->getDirection() == dir) {
            float noteY, targetY, offset;

            noteY = hold->getPosition().y;
            targetY = targetZones[(int)dir].getPosition().y;

            offset = abs(noteY - targetY);

            if (offset <= 50.f)
                hold->setIsHeld(true);
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

        if (valid)
            if (checkHit(dir)) {
                score += 100, combo++;
            }
            else
                combo = 0;

    }
}

void GameManager::update(float dt) {
    handleHeldInput();

    for (auto& note : arrows) {
        note->update(dt);
    }

    arrows.erase(
        remove_if(arrows.begin(), arrows.end(),
            [](const unique_ptr<Arrow>& notes) { return notes->isOffScreen() || notes->getIsPressed();
            }), arrows.end()); // stergem notele care au iesit de pe ecran
}

void GameManager::draw(sf::RenderWindow& window) {

    for (auto& note : targetZones)
        note.draw(window);

    for (auto& note : arrows)
        note->draw(window);
}

void GameManager::addNote(unique_ptr<Arrow> note) {
    arrows.push_back(std::move(note));
}