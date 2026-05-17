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
    selectedItemIndex = 0;

    sf::Text play(font, "PLAY", 60);
    play.setFillColor(sf::Color::Yellow);
    play.setPosition({750 - play.getLocalBounds().size.x / 2.f, 150});
    sf::Text exit(font, "EXIT", 60);
    exit.setFillColor(sf::Color::White);
    exit.setPosition({750 - exit.getLocalBounds().size.x / 2.f, 400});

    texts.push_back(play);
    texts.push_back(exit);
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
    } else {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = 1;
        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < texts.size()) {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
    } else {
        texts[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = 0;
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
                    if (selectedItemIndex == 0)
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
    cout << "Game run\n";
    return;
}


void Menu::runMenu() {
    bool start = runMenuLoop();

    while (start && window.isOpen())
        runGameplayLoop();
}