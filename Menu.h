#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "GameManager.h"
#include "Chart.h"

using namespace std;

class Menu {
private:
    sf::Font font;
    vector<sf::Text> texts;
    int selectedItemIndex;
    sf::RenderWindow window;

    vector<sf::Text> songs;
    int selectedSongIndex;
    vector<string> songFiles;

    vector<sf::Text> pauseOptions;
    int selectedPauseIndex;

    sf::Texture menuTexture;
    unique_ptr<sf::Sprite> menuBackground;

    bool runMenuLoop();
    void runSongSelectMenuLoop();
    void runGameplayLoop(int songIndex);

    void moveUp();
    void moveDown();
    void moveSongUp();
    void moveSongDown();
    void movePauseUp();
    void movePauseDown();
    void handleInput(sf::Event event);
    void handleInputSong(sf::Event event);
    void handleInputPause(sf::Event event);
public:
    Menu();

    void runMenu();

    int getSelecedItemIndex() const;
};