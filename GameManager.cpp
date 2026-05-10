#include "GameManager.h"
#include <cmath>
#include <iostream>
#include <memory>

using namespace std;

GameManager* GameManager::instance = nullptr;

void GameManager::checkHit(Direction dir) {
    for (auto& note : arrows) {
        if (note->getDirection() == dir) {
            float noteY, targetY, offset;

            noteY = note->getPosition().y;
            targetY = targetZones[(int)dir].getPosition().y;
            offset = abs(noteY - targetY);

            note->setIsPressed(true);

            if (offset <= 50.f) {
                score += 100;
                combo++;
            }else
                combo = 0;
        }
    }

}

void GameManager::checkHold(Direction dir) {
    for (auto& note : arrows) {
        auto hold = dynamic_cast<HoldArrow*>(note.get());

        if (hold && hold->getDirection() == dir) {
            float noteY, targetY, offset;

            noteY = hold->getPosition().y;
            targetY = targetZones[(int)dir].getPosition().y;

            offset = abs(noteY - targetY);

            if (offset <= 50.f) {
                hold->setIsHeld(true);
                score += 50;
                combo++;
            }else {
                hold->setMiss(true);
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

            for (auto& note : arrows) {
                if (note->getIsPlayerNote()) {
                    auto hold = dynamic_cast<HoldArrow*>(note.get());

                    if (hold && hold->getDirection() == dir) {
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
    for (auto& note : arrows) {
        auto hold = dynamic_cast<HoldArrow*>(note.get());

        if (hold && hold->getDirection() == dir)
            hold->setIsHeld(false);
    }
}

void GameManager::update(float dt) {
    handleHeldInput();

    for (auto& note : arrows) {
        auto hold = dynamic_cast<HoldArrow*>(note.get());

        if (hold) {
            hold->update(dt);
        }else
            note->update(dt);
    }

    arrows.erase(
        remove_if(arrows.begin(), arrows.end(),
            [](const unique_ptr<Arrow>& notes) {
                auto hold = dynamic_cast<HoldArrow*>(notes.get());

                if (hold)
                    return hold->isFinished() || hold->isMiss();
                else
                    return notes->isOffScreen() || notes->getIsPressed();
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

    score = 0;
    combo = 0;

    curr_song->play();
}
