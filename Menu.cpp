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

    songFiles = {"dadbattle-chart.json", "bopeebo-chart.json"};

    sf::Text song1(font, "SONG 1", 60), song2(font, "SONG 2", 60);
    song1.setPosition({580, 200});
    song2.setPosition({580, 300});

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
        for (auto& item : texts) window.draw(item);
        window.display();
    }

    return false;
}

void Menu::runGameplayLoop() {
    GameManager* gm = GameManager::getInstance();
    gm->preloadTextures();
    gm->loadTargetZones();

    Chart chart("dadbattle-chart.json", "hard");
    auto song = make_unique<Song>("Dad Battle", "Inst2.ogg", "Voices-bf2.ogg", "Voices-dad2.ogg", chart);
    gm->loadSong(move(song));

    sf::Clock clock;

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

            gm->handleInput(*event);
        }

        gm->handleHeldInput();
        gm->spawnNotes();
        gm->update(dt);

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

        window.draw(scoreText);
        window.draw(perfect);
        window.draw(misses);
        window.display();
    }
}


void Menu::runMenu() {
    bool start = runMenuLoop();

    while (start && window.isOpen())
        runGameplayLoop();
}