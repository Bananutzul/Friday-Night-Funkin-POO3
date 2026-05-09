#include <SFML/Graphics.hpp>
#include "Arrow.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "FNF");
    window.setFramerateLimit(60);

    // Creaza o sageata
    Arrow arrow(
        {400.f, 0.f},           // pozitie initiala
        200.f,                   // viteza// shape gol, Arrow il seteaza
        Direction::RIGHT,         // directie
        false                    // nu e apasata
    );

    Arrow arrow2(
    {300.f, 0.f},           // pozitie initiala
    200.f,                 // shape gol, Arrow il seteaza
    Direction::LEFT,         // directie
    false                    // nu e apasata
);


    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        arrow.update(dt);
        arrow2.update(dt);

        window.clear(sf::Color::Black);
        arrow.draw(window);
        arrow2.draw(window);
        window.display();
    }

    return 0;
}