#include <SFML/Graphics.hpp>
#include <fstream>



class Tile{
public:
    sf::Texture tileTexture;
    sf::Sprite tileSprite;

    Tile();
    Tile(int x, int y);
    void setPosition(float x, float y);
};