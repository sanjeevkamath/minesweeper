#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "welcomeWindow.h"
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,620), "My Program");
//    window.setFramerateLimit(60);
    sf::Font font;
    if(!font.loadFromFile("files/font.ttf")){
        cout << "Error Loading font file" << endl;
        system("pause");
    }
    sf::Text text;
    text.setFont( font );
    text.setString("Hello World");

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) cout << "1" << endl;

            window.clear();
            window.draw(text);
            window.display();

        }
    }

    return 0;
}


