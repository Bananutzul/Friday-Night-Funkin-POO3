#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "GameManager.h"
#include "Chart.h"

using namespace std;

class Menu {
private:
    sf::Font font;
    vector<sf::Text> texts;
    int selectedItemIndex;
    sf::RenderWindow window;

    bool runMenuLoop();
    void runGameplayLoop();

    void moveUp();
    void moveDown();
    void handleInput(sf::Event event);
public:
    Menu();

    void runMenu();

    int getSelecedItemIndex() const;
};