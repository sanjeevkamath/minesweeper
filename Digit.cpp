//
// Created by sanje on 8/2/2023.
//

#include "Digit.h"


Digit::Digit(){
// COMMENT - Tried to load textures through for loop; It would work, but it would keep throwing errors
//    for(int i = 0; i <= 10; i++){
//        {
//            sf::Texture temp;
//            temp.loadFromFile("files/images/digits.png", sf::IntRect(i * 21, 0, 21, 32));
//            digits.push_back(temp);
//        }
//    }
    zero.loadFromFile("files/images/digits.png",sf::IntRect(0,0,21,32));
    one.loadFromFile("files/images/digits.png",sf::IntRect(21,0,21,32));
    two.loadFromFile("files/images/digits.png",sf::IntRect(2 * 21,0,21,32));
    three.loadFromFile("files/images/digits.png",sf::IntRect(3 * 21,0,21,32));
    four.loadFromFile("files/images/digits.png",sf::IntRect(4 * 21,0,21,32));
    five.loadFromFile("files/images/digits.png",sf::IntRect(5 * 21,0,21,32));
    six.loadFromFile("files/images/digits.png",sf::IntRect(6 * 21,0,21,32));
    seven.loadFromFile("files/images/digits.png",sf::IntRect(7 * 21,0,21,32));
    eight.loadFromFile("files/images/digits.png",sf::IntRect(8* 21,0,21,32));
    nine.loadFromFile("files/images/digits.png",sf::IntRect(9 * 21,0,21,32));



}
void Digit::setSprite(sf::Sprite &input, unsigned int number){
    if (number == 0){
        input.setTexture(zero);
    }
    else if(number == 1){
        input.setTexture(one);
    }
    else if(number == 2){
        input.setTexture(two);
    }
    else if(number == 3){
        input.setTexture(three);
    }
    else if(number == 4){
        input.setTexture(four);
    }
    else if(number == 5){
        input.setTexture(five);
    }
    else if(number == 6){
        input.setTexture(six);
    }
    else if(number == 7){
        input.setTexture(seven);
    }
    else if(number == 8){
        input.setTexture(eight);
    }
    else if(number == 9) {
        input.setTexture(nine);
    }
}
