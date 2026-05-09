#include <SFML/Graphics.hpp>
#include "Arrow.h"
#include "HoldArrow.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 600}), "FNF");
    window.setFramerateLimit(60);

    HoldArrow arrow(
        {550.f, 600.f},
        200.f,
        Direction::RIGHT,
        false,
        4,
        false
    );

    HoldArrow arrow2(
    {400.f, 600.f},
    200.f,
    Direction::LEFT,
    false,
    4,
    false
);
    HoldArrow arrow3(
    {100.f, 600.f},
    200.f,
    Direction::DOWN,
    false,
    4,
    false
);
    HoldArrow arrow4(
    {250.f, 600.f},
    200.f,
    Direction::UP,
    false,
    4,
    false
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
        arrow3.update(dt);
        arrow4.update(dt);

        window.clear(sf::Color::Black);
        arrow.draw(window);
        arrow2.draw(window);
        arrow3.draw(window);
        arrow4.draw(window);
        window.display();
    }

    return 0;
}