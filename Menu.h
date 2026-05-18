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

    unique_ptr<sf::Text> high_score1;
    int high_score_nr1 = 0;
    unique_ptr<sf::Text> high_score2;
    int high_score_nr2 = 0;

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
    void loadScoreFromFile(int idx);
    void saveScoreToFile(int idx, int score);
public:
    Menu();

    void runMenu();

    int getSelecedItemIndex() const;
};