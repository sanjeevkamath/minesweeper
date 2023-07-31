#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cctype>
#include "window.h"
using namespace std;
void setText(sf::Text &text, float x, float y);
int main(){
    Window welcomeScreen;
    GameWindow gameScreen;
    string playerName = "";
    // Initialize Welcome Window
    sf::RenderWindow welcomeWindow(sf::VideoMode(welcomeScreen.width,welcomeScreen.height), "Minesweeper");
    welcomeWindow.setFramerateLimit(60);

    //Load font from provided file
    sf::Font font;
    if(!font.loadFromFile("files/font.ttf")){
        cout << "Error Loading font file" << endl;
        system("pause");
    }


    //Initialization for Welcome Text
    sf::Text welcomeText;
    welcomeText.setFont( font );
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setCharacterSize(24);
    setText(welcomeText, welcomeScreen.width/2.0f, welcomeScreen.height/2.0f -150);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);


    //Initialize name prompt
    sf::Text enterName;
    enterName.setFont( font );
    enterName.setString("Enter your name:");
    enterName.setFillColor(sf::Color::White);
    enterName.setCharacterSize(20);
    setText(enterName,welcomeScreen.width/2.0f, welcomeScreen.height/2.0f - 75 );
    enterName.setStyle(sf::Text::Bold);

    //Create text object for input Text
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setStyle(sf::Text::Bold);

    // Create a cursor object
    sf::Text cursorText;
    cursorText.setFont(font);
    cursorText.setCharacterSize(18);
    cursorText.setFillColor(sf::Color::White);
    cursorText.setString("|");


    while(welcomeWindow.isOpen()){

        sf::Event event;
        while(welcomeWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                welcomeWindow.close();
                return 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                if(playerName != ""){
                    welcomeWindow.close();
                    gameScreen.name = playerName;
                    // Call on game open game window
                    gameScreen.startGame();
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace) {
                if (!playerName.empty()) {
                    playerName.pop_back();
                }
            }


            // Input text from user
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    // Convert the entered character to lowercase if it's an alphabet
                    char inputChar = static_cast<char>(event.text.unicode);
                    if (isalpha(inputChar)) {
                        // Limit playerName to less than 10 characters
                        if (playerName.size() < 10) {
                            // Apply Capitalization rule
                            if (playerName.empty())
                                inputChar = std::toupper(inputChar); // Capitalize the first letter
                            else
                                inputChar = std::tolower(inputChar); // Convert to lowercase
                            playerName += inputChar;
                        }}}}

            // Update text and cursor on screen
            inputText.setString(playerName);
            setText(inputText, welcomeScreen.width/2.0f, welcomeScreen.height/2.0f -45);
            setText(cursorText, welcomeScreen.width/2.0f + inputText.getLocalBounds().width / 2.0,
                    welcomeScreen.height/2.0f -45);



            // Display Text
            welcomeWindow.clear(sf::Color::Blue);
            welcomeWindow.draw(welcomeText);
            welcomeWindow.draw(enterName);
            welcomeWindow.draw(inputText);
            welcomeWindow.draw(cursorText);
            welcomeWindow.display();

        }
    }


    cout << playerName;
    return 0;
}

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
    }


