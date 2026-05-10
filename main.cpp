#include <SFML/Graphics.hpp>
#include "Arrow.h"
#include "HoldArrow.h"
#include "GameManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1500, 600}), "FNF");
    window.setFramerateLimit(60);

    HoldArrow arrow(
        {1100.f, 600.f},
        200.f,
        Direction::RIGHT,
        false,
        true,
        2,
        false
    );

    HoldArrow arrow2(
    {950.f, 600.f},
    200.f,
    Direction::UP,
    false,
    true,
    4,
    false
);
    HoldArrow arrow3(
    {650.f, 600.f},
    200.f,
    Direction::LEFT,
    false,
    true,
    4,
    false
);
    HoldArrow arrow4(
    {800.f, 600.f},
    200.f,
    Direction::DOWN,
    false,
    true,
    4,
    false
);

    GameManager* gm = GameManager::getInstance();

    gm->addNote(make_unique<HoldArrow>(arrow));
    gm->addNote(make_unique<HoldArrow>(arrow2));
    gm->addNote(make_unique<Arrow>(arrow3));
    gm->addNote(make_unique<Arrow>(arrow4));

    Chart chart("bopeebo-chart.json", "hard");
    auto song = make_unique<Song>("Bopeebo", "bopeebo.mp3", chart);
    gm->loadSong(std::move(song));

    auto playerNotes = chart.getPlayerNotes();
    auto opponentNotes = chart.getOpponentNotes();
    cout << "Opponent notes: " << opponentNotes.size() << endl;
    cout << "Player notes: " << playerNotes.size() << "\n";
    for (int i = 0; i < 10 && i < playerNotes.size(); i++) {
        cout << "t=" << playerNotes[i].time
             << " dir=" << (int)playerNotes[i].direction
             << " dur=" << playerNotes[i].duration << "\n";
    }



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

        gm->spawnNotes();
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