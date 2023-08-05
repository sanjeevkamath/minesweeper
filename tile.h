#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Tile{
public:

    sf::Texture hiddenTexture;
    sf::Texture revealedTexture;
    sf::Texture numberTexture;
    sf::Texture tileTexture;
    sf::Texture flagTexture;
    sf::Texture mineTexture;
    sf::Texture pauseTexture;
    sf::Sprite numberSprite;
    sf::Sprite tileSprite;
    sf::Sprite flagSprite;
    sf::Sprite mineSprite;
    sf::Sprite pauseSprite;

    bool flag = false;
    bool hidden = true;
    bool hasMine = false;

    int neighboringMines = 0;
    string numMinesString = "files/images/number_";
    std::vector<Tile*> adjacentTiles;



    Tile(int x, int y);
    void exposeTile();
    void markFlag();
    void revealEmptyTiles();
};