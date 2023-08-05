#include <fstream>
#include<iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "tile.h"
#include "mine.h"
#include "Digit.h"

using namespace std;
class Window{
public:
    string name = "";
    float width, height;
    int rows, columns, mines;
    Window();   //Default Constructor
};

class GameWindow : public Window{
    int tileCount = rows * columns;

    sf::RenderWindow window;

    //Set Textures Buttons
    sf::Texture happyFaceTexture;
    sf::Texture debugTexture;
    sf::Texture playTexture, pauseTexture, leaderboardTexture;
    sf::Texture negativeTexture;

    Digit digits;

    sf::Sprite happyFaceSprite;
    sf::Sprite debugSprite;
    sf::Sprite playSprite;
    sf::Sprite pauseSprite;
    sf::Sprite leaderboardSprite;
    sf::Sprite counterHundreds;
    sf::Sprite counterTens;
    sf::Sprite counterOnes;
    sf::Sprite negativeSprite;
    sf::Sprite tenMinutes;
    sf::Sprite minutes, tenSeconds, seconds;

    bool pause = false;
    bool debug = false;
    bool victory = false;
    bool newGame = false;

    vector<vector<Tile>> tiles;

    int remainingMines;

    void updateCounter();
    void updateTimer(int timeSeconds);
    void checkAdjacent();
    bool checkVictory();
    void debugTiles();
public:
    void startGame();
    GameWindow();

};

