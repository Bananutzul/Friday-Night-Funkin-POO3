#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Arrow.h"
#include "HoldArrow.h"
#include "GameManager.h"
#include "Menu.h"

int main() {
    Menu menu;

    menu.runMenu();

    //
    // sf::RenderWindow window(sf::VideoMode({1500, 600}), "FNF");

    // sf::RenderWindow window(sf::VideoMode({1500, 600}), "FNF");
    // window.setFramerateLimit(60);
    //
    // GameManager* gm = GameManager::getInstance();
    //
    // gm->preloadTextures();
    // gm->loadTargetZones();
    //
    // Chart chart("dadbattle-chart.json", "hard");
    // auto song = make_unique<Song>("Dad Battle", "Inst2.ogg", "Voices-bf2.ogg", "Voices-dad2.ogg", chart);
    // gm->loadSong(std::move(song));
    //
    // sf::Clock clock;
    //
    // sf::Font font;
    // font.openFromFile("font.ttf");
    //
    // sf::Text scoreText(font);
    // scoreText.setCharacterSize(24);
    // scoreText.setFillColor(sf::Color::White);
    // scoreText.setPosition({10.f, 30.f});
    //
    // sf::Text perfect(font);
    // perfect.setCharacterSize(24);
    // perfect.setPosition({750.f, 40.f});
    //
    // sf::Text misses(font);
    // misses.setCharacterSize(24);
    // misses.setPosition({10.f, 80.f});
    // misses.setFillColor(sf::Color::Red);
    //
    //
    // while (window.isOpen()) {
    //     float dt = clock.restart().asSeconds();
    //
    //     while (const auto event = window.pollEvent()) {
    //         if (event->is<sf::Event::Closed>())
    //             window.close();
    //
    //         gm->handleInput(*event);
    //     }
    //
    //     gm->handleHeldInput();
    //     gm->spawnNotes();
    //     gm->update(dt);
    //
    //     window.clear(sf::Color::Black);
    //     gm->draw(window);
    //     gm->drawTargetZones(window);
    //
    //     scoreText.setString("Score: " + to_string(gm->getScore()));
    //     misses.setString("Misses: " + to_string(gm->getMisses()));
    //     string aux = gm->getPerfect();
    //
    //     if (aux == "Perfect!")
    //         perfect.setFillColor(sf::Color::Green);
    //     else if (aux == "Great!")
    //         perfect.setFillColor(sf::Color::Blue);
    //     else if (aux == "Good!")
    //         perfect.setFillColor(sf::Color::Yellow);
    //     else if (aux == "Miss!")
    //         perfect.setFillColor(sf::Color::Red);
    //
    //     perfect.setString(aux);
    //
    //     window.draw(scoreText);
    //     window.draw(perfect);
    //     window.draw(misses);
    //     window.display();
    // }

    return 0;
}