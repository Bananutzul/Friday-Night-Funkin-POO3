#include <SFML/Graphics.hpp>
#include "Arrow.h"
#include "HoldArrow.h"
#include "GameManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 600}), "FNF");
    window.setFramerateLimit(60);

    HoldArrow arrow(
        {600.f, 600.f},
        200.f,
        Direction::RIGHT,
        false,
        2,
        false
    );

    HoldArrow arrow2(
    {450.f, 600.f},
    200.f,
    Direction::UP,
    false,
    4,
    false
);
    HoldArrow arrow3(
    {150.f, 600.f},
    200.f,
    Direction::LEFT,
    false,
    4,
    false
);
    HoldArrow arrow4(
    {300.f, 600.f},
    200.f,
    Direction::DOWN,
    false,
    4,
    false
);

    GameManager* gm = GameManager::getInstance();

    gm->addNote(make_unique<HoldArrow>(arrow));
    gm->addNote(make_unique<Arrow>(arrow2));
    gm->addNote(make_unique<Arrow>(arrow3));
    gm->addNote(make_unique<Arrow>(arrow4));

    sf::Clock clock;

    sf::Font font;
    font.openFromFile("font.ttf");

    sf::Text scoreText(font), comboText(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});
    comboText.setCharacterSize(24);
    comboText.setFillColor(sf::Color::White);
    comboText.setPosition({10.f, 40.f});


    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            gm->handleInput(*event);
        }

        gm->update(dt);

        window.clear(sf::Color::Black);
        gm->draw(window);

        scoreText.setString("Score: " + to_string(gm->getScore()));
        comboText.setString("Combo: " + to_string(gm->getCombo()));

        window.draw(scoreText);
        window.draw(comboText);
        window.display();
    }

    return 0;
}