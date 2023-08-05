#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>

class Digit {
public:
    std::vector<sf::Texture> digits;

    sf::Texture zero;
    sf::Texture one;
    sf::Texture two;
    sf::Texture three;
    sf::Texture four;
    sf::Texture five;
    sf::Texture six;
    sf::Texture seven;
    sf::Texture eight;
    sf::Texture nine;
    Digit();
    void setSprite(sf::Sprite &input,unsigned int number);
};





