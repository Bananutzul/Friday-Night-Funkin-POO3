#include "GameManager.h"
#include <cmath>
#include <iostream>
#include <memory>

using namespace std;

GameManager* GameManager::instance = nullptr;

void GameManager::checkHit(Direction dir) {
    Arrow* closest = nullptr;
    float minOffset = 9999.f;

    for (auto& note : player_arrows) {
        if (note->getIsPlayerNote()) {
            if (note->getDirection() == dir && note->getPosition().y >= -15.f) {
                float noteY, targetY, offset;

                noteY = note->getPosition().y;
                targetY = targetZones[(int)dir].getPosition().y;
                offset = abs(noteY - targetY);

                if (offset < minOffset) {
                    minOffset = offset;
                    closest = note.get();
                }
            }
        }
    }

    if (closest && minOffset <= 90.f) {

        hasReleasedDir[(int)dir] = false;

        if (abs(minOffset) <= 15.f)
            perfect = "Perfect!", score += 250;
        else if (abs(minOffset) <= 40.f)
            perfect = "Great!", score += 150;
        else if (abs(minOffset) <= 90.f)
            perfect = "Good!", score += 100;

        if (player) player->setState(PlayerState::HIT);

        closest->setIsPressed(true);

        targetZones[(int)dir].setState(targetState::HIT);
    }
    else if (closest && minOffset <= 250.f) {
        hasReleasedDir[(int)dir] = false;
        perfect = "Miss!";
        if (player) player->setState(PlayerState::MISS);
        misses++;
    }
}

void GameManager::checkHold(Direction dir) {
    HoldArrow* closest = nullptr;
    float minOffset = 9999.f;

    for (auto& note : player_holdarrows) {

        if (note->getDirection() == dir && note->getIsPlayerNote() && note->getPosition().y >= -15.f) {
            float noteY, targetY, offset;

            noteY = note->getPosition().y;
            targetY = targetZones[(int)dir].getPosition().y;

            offset = abs(noteY - targetY);

            if (offset < minOffset) {
                minOffset = offset;
                closest = note.get();
            }
        }
    }

    if (closest && minOffset <= 90.f && hasReleasedDir[(int)dir] == true) {
        hasReleasedDir[(int)dir] = false;

        if (abs(minOffset) <= 15.f)
            perfect = "Perfect!", score += 250;
        else if (abs(minOffset) <= 40.f)
            perfect = "Great!", score += 150;
        else if (abs(minOffset) <= 90.f)
            perfect = "Good!", score += 100;

        if (player) player->setState(PlayerState::HIT);

        closest->setIsHeld(true);
        targetZones[(int)dir].setState(targetState::HIT);
        closest->setIsVisible(false);
        score += 50;

    }else if (closest && minOffset <= 250.f && closest->getHasBeenHeld() == false && hasReleasedDir[(int)dir] == true) {
        hasReleasedDir[(int)dir] = false;
        closest->setHasBeenHeld(true);
        perfect = "Miss!";
        if (player) player->setState(PlayerState::MISS);
        misses++;
    }
}

void GameManager::handleHeldInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        checkHold(Direction::LEFT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        checkHold(Direction::DOWN);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        checkHold(Direction::RIGHT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        checkHold(Direction::UP);
}

void GameManager::handleInput(sf::Event event) {
    if (const auto& keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        Direction dir;
        bool valid = true;

        switch (keyEvent->code) {
            case sf::Keyboard::Key::A:
            case sf::Keyboard::Key::Left:
                dir = Direction::LEFT;
                break;
            case sf::Keyboard::Key::S:
            case sf::Keyboard::Key::Down:
                dir = Direction::DOWN;
                break;
            case sf::Keyboard::Key::D:
            case sf::Keyboard::Key::Right:
                dir = Direction::RIGHT;
                break;
            case sf::Keyboard::Key::W:
            case sf::Keyboard::Key::Up:
                dir = Direction::UP;
                break;
            default:
                valid = false;
                break;
        }

        if (valid && hasReleasedDir[(int)dir] == true){
            targetZones[(int)dir].setState(targetState::PRESSED);
            checkHit(dir);
        }
    }

    if (const auto& keyEvent = event.getIf<sf::Event::KeyReleased>()) {
        Direction dir;
        bool valid = true;

        switch (keyEvent->code) {
            case sf::Keyboard::Key::A:
            case sf::Keyboard::Key::Left:
                dir = Direction::LEFT;
                break;
            case sf::Keyboard::Key::S:
            case sf::Keyboard::Key::Down:
                dir = Direction::DOWN;
                break;
            case sf::Keyboard::Key::W:
            case sf::Keyboard::Key::Up:
                dir = Direction::UP;
                break;
            case sf::Keyboard::Key::D:
            case sf::Keyboard::Key::Right:
                dir = Direction::RIGHT;
                break;
            default:
                valid = false;
                break;
        }

        if (valid) {
            releaseHold(dir);
            hasReleasedDir[(int)dir]= true;
            perfect = "";
            targetZones[(int)dir].setState(targetState::IDLE);
        }
    }
}

void GameManager::releaseHold(Direction dir) {
    for (auto& hold : player_holdarrows) {
        if (hold->getDirection() == dir && hold->getIsPlayerNote() && hold->getIsHeld() == true)
            hold->setIsHeld(false);
    }
}

void GameManager::update(float dt) {

    if (!songStarted) {
        gameTimeMs += 1000.f * dt;

        if (gameTimeMs >= 0) {
            gameTimeMs = 0;
            curr_song->play();
            songStarted = true;
        }
    }else {
        gameTimeMs = curr_song->getTimeMs();
    }

    float beat = introDurationMs / 4.f;

    if (!played1 && gameTimeMs >= -introDurationMs)
        sound1->play(), played1 = true;
    if (!played2 && gameTimeMs >= -introDurationMs + beat)
        sound2->play(), played2 = true;
    if (!played3 && gameTimeMs >= -introDurationMs + beat * 2)
        sound3->play(), played3 = true;
    if (!playedGo && gameTimeMs >= -introDurationMs + beat * 3)
        soundGo->play(), playedGo = true;

    if (player) {
        player->update(dt);
    }

    updateNotes(player_arrows, dt);
    updateNotes(player_holdarrows, dt);
    updateNotes(opponent_arrows, dt);
    updateNotes(opponent_holdarrows, dt);

    for (auto& note : player_arrows) {
        if (note->isOffScreen()) {
            perfect = "Miss!";
            player->setState(PlayerState::MISS);
            misses++;
        }
    }

    for (auto& note : player_holdarrows) {
        if (!note->getHasBeenTriggered()) {
            if (note->isFinished()) {
                note->setHasBeenTriggered(true);

                if (!note->getHeldEnough()) {
                    perfect = "Miss!";
                    player->setState(PlayerState::MISS);
                    misses++;
                }
            }else if (note->isOffScreen()) {
                note->setHasBeenTriggered(true);

                if (!note->getHeldEnough()) {
                    perfect = "Miss!";
                    player->setState(PlayerState::MISS);
                    misses++;
                }
            }
        }
    }

    bool justPressed[4] = {false, false, false, false};

    for (auto& note : opponent_arrows) {
        Direction dir = note->getDirection();

        if (note->getPosition().y <= 0) {
            targetZones[(int)dir + 4].setState(targetState::HIT);
            note->setIsVisible(false);
            justPressed[(int)dir] = true;
        }
    }

    for (auto& note : opponent_holdarrows) {
        Direction dir = note->getDirection();

        if (note->getPosition().y <= 0.f) {
            targetZones[(int)dir + 4].setState(targetState::HIT);
            note->setIsVisible(false);
            note->setIsHeld(true);
            justPressed[(int)dir] = true;
        }
    }

    for (int i = 4; i < 8; i++) {
        if (justPressed[i - 4])
            continue;

        if (targetZones[i].getState() == targetState::HIT) {
            bool playing = false; // bool pt verificare daca mai sunt note pe targetzone

            for (auto& note : opponent_arrows) {
                if (note->getDirection() == targetZones[i].getDirection() && note->getPosition().y <= 0.f && note->getIsPlayerNote() == false) {
                    playing = true;
                    break;
                }
            }

            for (auto& note : opponent_holdarrows) {
                if (note->getDirection() == targetZones[i].getDirection() && note->getIsHeld() && !note->isFinished()) {
                    playing = true;
                    break;
                }
            }

            if (!playing)
                targetZones[i].setState(targetState::IDLE);
        }
    }

    eraseNotes(player_arrows, [](const unique_ptr<Arrow>& note) {
        return note->isOffScreen() || note->getIsPressed();
    });

    eraseNotes(player_holdarrows, [](const unique_ptr<HoldArrow>& note) {
        return note->isMiss() || note->isFinished() || note->isOffScreen();
    });

    eraseNotes(opponent_arrows, [](const unique_ptr<Arrow>& note) {
        return note->isOffScreen();
    });

    eraseNotes(opponent_holdarrows, [](const unique_ptr<HoldArrow>& note) {
        return note->isOffScreen() || note->isFinished();
    });


}

void GameManager::draw(sf::RenderWindow& window) {

    if (background1)
        window.draw(*background1);

    if (background2)
        window.draw(*background2);

    if (player) {
        player->draw(window);
    }

    for (auto& note : player_arrows)
        note->draw(window);
    for (auto& hold : player_holdarrows)
        hold->draw(window);
    for (auto& note : opponent_arrows)
        note->draw(window);
    for (auto& hold : opponent_holdarrows)
        hold->draw(window);
}

int GameManager::getScore() const {
    return score;
}

void GameManager::loadSong(unique_ptr<Song> song) {
    curr_song = std::move(song);

    buf1.loadFromFile("intro1.ogg");
    sound1->setBuffer(buf3);
    buf2.loadFromFile("intro2.ogg");
    sound2->setBuffer(buf2);
    buf3.loadFromFile("intro3.ogg");
    sound3->setBuffer(buf1);
    bufGo.loadFromFile("introGo.ogg");
    soundGo->setBuffer(bufGo);

    playerNotes = curr_song->getChart().getPlayerNotes();
    opponentNotes = curr_song->getChart().getOpponentNotes();

    nextPlayerNote = 0;
    nextOpponentNote = 0;

    player_arrows.clear();
    player_holdarrows.clear();
    opponent_arrows.clear();
    opponent_holdarrows.clear();

    score = 0;

    int bpm = curr_song->getBpm();
    float beatDuration = (60.f * 1000.f) / (float)bpm;
    introDurationMs = beatDuration * 4;

    gameTimeMs = -introDurationMs;

    songStarted = false;
    played1 = false, played2 = false, played3 = false, playedGo = false;
}

void GameManager::spawnNotes() {
    float current_timeMs = gameTimeMs;
    travelTime = 550.f / (200.f * curr_song->getSpeedMultiplier()) * 1000.f;

    while (nextPlayerNote < playerNotes.size()) {
        auto& note = playerNotes[nextPlayerNote];

        if (current_timeMs >= note.time - travelTime) {

            float x;

            switch (note.direction) {
                case Direction::LEFT: x = 700.f;break;
                case Direction::DOWN: x = 840.f;break;
                case Direction::UP: x = 980.f;break;
                case Direction::RIGHT: x = 1120.f;break;
            }

            if (note.duration > 0) {
                player_holdarrows.push_back(make_unique<HoldArrow>(sf::Vector2f({x, 600.f}), 200.f * curr_song->getSpeedMultiplier(), note.direction, false, textures["arrows"], true, note.duration / 1000.f, false));
            }else {
                player_arrows.push_back(make_unique<Arrow>(sf::Vector2f({x, 600.f}), 200.f * curr_song->getSpeedMultiplier(), note.direction, false, true, textures["arrows"]));
            }

            nextPlayerNote++;
        }else break;
    }

    while (nextOpponentNote < opponentNotes.size()) {
        auto& note = opponentNotes[nextOpponentNote];

        if (current_timeMs >= note.time - travelTime) {

            float x;

            switch (note.direction) {
                case Direction::LEFT: x = 100.f;break;
                case Direction::DOWN: x = 240.f;break;
                case Direction::UP: x = 380.f;break;
                case Direction::RIGHT: x = 520.f;break;
            }

            if (note.duration > 0) {
               opponent_holdarrows.push_back(make_unique<HoldArrow>(sf::Vector2f({x, 600.f}), 200.f * curr_song->getSpeedMultiplier(), note.direction, false, textures["arrows"], false, note.duration / 1000.f, false));
            }else {
                opponent_arrows.push_back(make_unique<Arrow>(sf::Vector2f({x, 600.f}), 200.f * curr_song->getSpeedMultiplier(), note.direction, false, false, textures["arrows"]));
            }

            nextOpponentNote++;
        }else break;
    }
}

void GameManager::preloadTextures() {
    sf::Texture texture;
    texture.loadFromFile("arrows.png");
    textures["arrows"] = std::move(texture);

    if (playerTexture.loadFromFile("BOYFRIEND.png")) {
        player = std::make_unique<Player>(playerTexture);
    } else {
        cout << "Eroare la incarcarea sprite sheet-ului pt player!\n";
    }

    if (backgroundTexture1.loadFromFile("stageback.png")) {
        background1 = make_unique<sf::Sprite>(backgroundTexture1);
        background1->setScale({1300.f / backgroundTexture1.getSize().x, 700.f / backgroundTexture1.getSize().y});
    }
    else cout << "Eroare la incarcarea sprite-ului pt background layer 1!\n";

    if (backgroundTexture2.loadFromFile("bg.png")) {
        background2 = make_unique<sf::Sprite>(backgroundTexture2);
        background2->setScale({1300.f / backgroundTexture2.getSize().x, 700.f / backgroundTexture2.getSize().y});
    }
    else cout << "Eroare la incarcarea sprite-ului pt background layer 2!\n";
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

void GameManager::addNote(unique_ptr<Arrow> note) {
    if (note->getIsPlayerNote())
        player_arrows.push_back(std::move(note));
    else
        opponent_arrows.push_back(std::move(note));
}

void GameManager::addNote(unique_ptr<HoldArrow> note) {
    if (note->getIsPlayerNote())
        player_holdarrows.push_back(std::move(note));
    else
        opponent_holdarrows.push_back(std::move(note));
}

string GameManager::getPerfect() const {
    return perfect;
}

int GameManager::getMisses() const {
    return misses;
}
