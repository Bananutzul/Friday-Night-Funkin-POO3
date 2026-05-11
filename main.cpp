#include <SFML/Graphics.hpp>
#include "Arrow.h"
#include "HoldArrow.h"
#include "GameManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1500, 600}), "FNF");
    window.setFramerateLimit(60);

    GameManager* gm = GameManager::getInstance();

    gm->preloadTextures();
    gm->loadTargetZones();

    HoldArrow arrow(
        {1100.f, 600.f},
        200.f,
        Direction::RIGHT,
        false,
        gm->getTexture()["arrows"],
        true,
        2,
        false
    );

    HoldArrow arrow2(
    {950.f, 600.f},
    200.f,
    Direction::UP,
    false,
    gm->getTexture()["arrows"],
    true,
    4,
    false
);
    HoldArrow arrow3(
    {650.f, 600.f},
    200.f,
    Direction::LEFT,
    false,
    gm->getTexture()["arrows"],
    true,
    4,
    false
);
    HoldArrow arrow4(
    {800.f, 600.f},
    200.f,
    Direction::DOWN,
    false,
    gm->getTexture()["arrows"],
    true,
    4,
    false
);


    gm->addNote(make_unique<HoldArrow>(arrow));
    gm->addNote(make_unique<HoldArrow>(arrow2));
    gm->addNote(make_unique<Arrow>(arrow3));
    gm->addNote(make_unique<Arrow>(arrow4));

    Chart chart("bopeebo-chart.json", "hard");
    auto song = make_unique<Song>("Bopeebo", "Inst.ogg", "Voices-bf.ogg", "Voices-dad.ogg", chart);
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

    sf::Text scoreText(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});


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
        gm->drawTargetZones(window);
        gm->draw(window);

        scoreText.setString("Score: " + to_string(gm->getScore()));

        window.draw(scoreText);
        window.display();
    }

    return 0;
}