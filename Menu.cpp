#include "Menu.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "GameManager.h"
#include "Chart.h"

Menu::Menu() : window(sf::VideoMode({1500, 600}), "FNF") {
    window.setFramerateLimit(60);

    font.openFromFile("font.ttf");
    selectedItemIndex = 2;
    selectedSongIndex = 0;
    selectedPauseIndex = 0;

    songFiles = {"dadbattle-chart.json", "bopeebo-chart.json"};

    sf::Text song1(font, "SONG 1", 60), song2(font, "SONG 2", 60);
    song1.setPosition({550, 200});
    song2.setPosition({550, 300});
    song1.setFillColor(sf::Color::Cyan);
    song2.setFillColor(sf::Color::White);

    songs.push_back(song1);
    songs.push_back(song2);

    sf::Text title1(font, "FRIDAY NIGHT FUNKIN'", 90);
    title1.setFillColor(sf::Color::Yellow);
    title1.setPosition({130, 70});
    sf::Text title2(font, "OOP Project 3 - Zamfir Horia", 50);
    title2.setFillColor(sf::Color::White);
    title2.setPosition({230, 190});
    sf::Text play(font, "PLAY", 50);
    play.setFillColor(sf::Color::Yellow);
    play.setPosition({580, 300});
    sf::Text exit(font, "EXIT", 35);
    exit.setFillColor(sf::Color::White);
    exit.setPosition({592, 400});

    texts.push_back(title1);
    texts.push_back(title2);
    texts.push_back(play);
    texts.push_back(exit);

    sf::Text resume(font, "RESUME", 50), exit2(font, "EXIT", 50);
    resume.setFillColor(sf::Color::White);
    resume.setPosition({20, 250});
    exit2.setFillColor(sf::Color::White);
    exit2.setPosition({20, 350});

    pauseOptions.push_back(resume);
    pauseOptions.push_back(exit2);
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 == 2) {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
    } else {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = 3;
        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveSongUp() {
    if (selectedSongIndex - 1 >= 0) {
        songs[selectedSongIndex].setFillColor(sf::Color::White);
        selectedSongIndex--;
        songs[selectedSongIndex].setFillColor(sf::Color::Cyan);
    } else {
        songs[selectedSongIndex].setFillColor(sf::Color::White);
        selectedSongIndex = 1;
        songs[selectedSongIndex].setFillColor(sf::Color::Cyan);
    }
}

void Menu::movePauseUp() {
    if (selectedPauseIndex - 1 >= 0) {
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::White);
        selectedPauseIndex--;
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::Cyan);
    } else {
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::White);
        selectedPauseIndex = 1;
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::Cyan);
    }
}


void Menu::moveDown() {
    if (selectedItemIndex + 1 == 4) {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = 2;
        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
    } else {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = 3;
        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveSongDown() {
    if (selectedSongIndex + 1 < songs.size()) {
        songs[selectedSongIndex].setFillColor(sf::Color::White);
        selectedSongIndex++;
        songs[selectedSongIndex].setFillColor(sf::Color::Cyan);
    } else {
        songs[selectedSongIndex].setFillColor(sf::Color::White);
        selectedSongIndex = 0;
        songs[selectedSongIndex].setFillColor(sf::Color::Cyan);
    }
}

void Menu::movePauseDown() {
    if (selectedPauseIndex + 1 < pauseOptions.size()) {
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::White);
        selectedPauseIndex++;
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::Cyan);
    } else {
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::White);
        selectedPauseIndex = 0;
        pauseOptions[selectedPauseIndex].setFillColor(sf::Color::Cyan);
    }
}


void Menu::handleInput(sf::Event event) {
    if (const auto& keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        switch (keyEvent->code) {
            case sf::Keyboard::Key::Down:
                moveDown();
                break;
            case sf::Keyboard::Key::Up:
                moveUp();
                break;
            default:
                break;
        }
    }
}

void Menu::handleInputSong(sf::Event event) {
    if (const auto& keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        switch (keyEvent->code) {
            case sf::Keyboard::Key::Down:
                moveSongDown();
                break;
            case sf::Keyboard::Key::Up:
                moveSongUp();
                break;
            default:
                break;
        }
    }
}

void Menu::handleInputPause(sf::Event event) {
    if (const auto& keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        switch (keyEvent->code) {
            case sf::Keyboard::Key::Down:
                movePauseDown();
                break;
            case sf::Keyboard::Key::Up:
                movePauseUp();
                break;
            default:
                break;
        }
    }
}


bool Menu::runMenuLoop() {
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return false;
            }

            handleInput(*event);

            if (const auto& keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Enter) {
                    if (selectedItemIndex == 2)
                        return true;
                    return false;
                }
            }
        }
        window.clear(sf::Color(20, 20, 20));
        for (auto& item : texts)
            window.draw(item);
        window.display();
    }

    return false;
}

void Menu::runSongSelectMenuLoop() {
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            handleInputSong(*event);

            if (const auto& keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Escape)
                    return;

                if (keyEvent->code == sf::Keyboard::Key::Enter) {
                    if (selectedSongIndex == 0)
                        runGameplayLoop(1);
                    else runGameplayLoop(2);

                }
            }
        }
        window.clear(sf::Color(20, 20, 20));
        for (auto& item : songs)
            window.draw(item);
        window.display();
    }
}


void Menu::runGameplayLoop(int songIndex) {
    GameManager* gm = GameManager::getInstance();
    gm->preloadTextures();
    gm->loadTargetZones();

    unique_ptr<Chart> chart;

    if (songIndex == 2)
        chart = make_unique<Chart>("dadbattle-chart.json", "hard"), cout << 2;
    else
        chart = make_unique<Chart>("bopeebo-chart.json", "hard"), cout << 1;

    unique_ptr<Song> song;

    if (songIndex == 2)
        song = make_unique<Song>("Dad Battle", "Inst2.ogg", "Voices-bf2.ogg", "Voices-dad2.ogg", *chart);
    else
        song = make_unique<Song>("Bopeebo", "Inst.ogg", "Voices-bf.ogg", "Voices-dad.ogg", *chart);

    gm->loadSong(move(song));

    sf::Clock clock;
    bool isPaused = false;

    sf::Text scoreText(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 30.f});

    sf::Text perfect(font);
    perfect.setCharacterSize(24);
    perfect.setPosition({750.f, 40.f});

    sf::Text misses(font);
    misses.setCharacterSize(24);
    misses.setPosition({10.f, 80.f});
    misses.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto& keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Escape && gm->getCountdownFinished()) {
                    isPaused = !isPaused;

                    if (isPaused) {
                        gm->pauseMusic();
                    }else {
                        gm->resumeMusic();
                    }
                }

                if (isPaused) {
                    if (keyEvent->code == sf::Keyboard::Key::Enter) {
                        if (selectedPauseIndex == 0) {
                            isPaused = false;
                            gm->resumeMusic();
                        }else {
                            gm->stopMusic();
                            return;
                        }
                    }
                }
            }

            if (!isPaused)
                gm->handleInput(*event);
            else
                handleInputPause(*event);
        }

        if (!isPaused) {
            gm->handleHeldInput();
            gm->spawnNotes();
            gm->update(dt);
        }

        window.clear(sf::Color::Black);
        gm->draw(window);
        gm->drawTargetZones(window);

        scoreText.setString("Score: " + to_string(gm->getScore()));
        misses.setString("Misses: " + to_string(gm->getMisses()));
        string aux = gm->getPerfect();

        if (aux == "Perfect!") perfect.setFillColor(sf::Color::Green);
        else if (aux == "Great!") perfect.setFillColor(sf::Color::Blue);
        else if (aux == "Good!") perfect.setFillColor(sf::Color::Yellow);
        else if (aux == "Miss!") perfect.setFillColor(sf::Color::Red);

        perfect.setString(aux);

        if (isPaused) {
            sf::RectangleShape dimOverlay({1500.f, 600.f});
            dimOverlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(dimOverlay);

            for (auto& item : pauseOptions) {
                window.draw(item);
            }
        }

        window.draw(scoreText);
        window.draw(perfect);
        window.draw(misses);
        window.display();
    }
}


void Menu::runMenu() {
    while (window.isOpen()) {
        bool start = runMenuLoop();

        if (start)
            runSongSelectMenuLoop();
        else break;
    }
}