#include <fstream>
#include<iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <sstream>
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
    void setText(sf::Text &text, float x, float y);
    };

class GameWindow : public Window{
    int tileCount = rows * columns;

    sf::RenderWindow window;

    //Set Textures Buttons
    sf::Texture happyFaceTexture, sunglassesTexture, deadFaceTexture;
    sf::Texture debugTexture;
    sf::Texture playTexture, pauseTexture, leaderboardTexture;
    sf::Texture negativeTexture;

    Digit digits;
    sf::Sprite happyFaceSprite, debugSprite, playSprite, pauseSprite, leaderboardSprite;
    sf::Sprite counterHundreds, counterTens, counterOnes;
    sf::Sprite negativeSprite;
    sf::Sprite tenMinutes, minutes, tenSeconds, seconds;


    bool pause = false;
    bool debug = false;
    bool victory = false;
    bool newGame = false;
    bool leaderboardBool = false;
    bool leaderboardPause = false;
    bool defeat = false;

    vector<vector<Tile>> tiles;

    int remainingMines;
    int victoryCounter = 1;

    void updateCounter();
    void updateTimer(int timeSeconds);
    void checkAdjacent();
    bool checkVictory();
public:
    void startGame();
    GameWindow();


};


class LeaderBoardWindow : public Window{
    sf::Text headerText;
    sf::Text bodyText;
public:

    struct Leaders{
        string leaderName;
        string time;
    };
    LeaderBoardWindow();
    void openLeaderBoard();
    vector<Leaders> rankings;
    string leaderString = "";
    void checkLeader(string& partName,  string& finalTime);

    };

