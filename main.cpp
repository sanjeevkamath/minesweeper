#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,620), "My Program");
    window.setFramerateLimit(60);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) cout << "1" << endl;
            cout << "TEST " << endl;

        }
    }
    return 0;
}


