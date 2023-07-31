//
// Created by sanjeev on 7/27/2023.
//
#include <fstream>
#include "window.h"
#include "tile.h"
#include <vector>


Window::Window() {
    ifstream file("files/board_config.cfg");
    if (file.is_open()) {
        // Input number of rows, columns, and mines
        file >> columns >> rows >> mines;
        width = columns * 32;
        height = (rows * 32) + 100;
    } else {
        cout << "Error opening board configuration file." << endl;
    }
}

void GameWindow::startGame() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");


    vector<vector<Tile>> tiles;
    for (int i = 0; i < rows; i++) {
        vector<Tile> row;
        for (int j = 0; j < columns; j++) {
            Tile tile(j*32, i*32);
//            tile.tileSprite.setPosition(j*32, i*32);
            row.push_back(tile);
        }
        tiles.push_back(row);
    }

    //Implement Buttons
    sf::Texture happyFaceTexture;
    sf::Texture debugTexture;
    sf::Texture playTexture, pauseTexture, leaderboardTexture;

    happyFaceTexture.loadFromFile("files/images/face_happy.png");
    debugTexture.loadFromFile("files/images/debug.png");
    playTexture.loadFromFile("files/images/play.png");
    pauseTexture.loadFromFile("files/images/pause.png");
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");

    sf::Sprite happyFaceSprite(happyFaceTexture);
    sf::Sprite debugSprite(debugTexture);
    sf::Sprite playSprite(playTexture);
    sf::Sprite pauseSprite(pauseTexture);
    sf::Sprite leaderboardSprite(leaderboardTexture);

    happyFaceSprite.setPosition((columns / 2.0) * 32 - 32,
                                32 * (rows + 0.5f));
    debugSprite.setPosition((columns * 32) - 304,
                                32 * (rows + 0.5f));
    playSprite.setPosition((columns * 32) - 240,
            32 * (rows + 0.5f));
    pauseSprite.setPosition((columns * 32) - 240,
                            32 * (rows + 0.5f));
    leaderboardSprite.setPosition((columns * 32) - 176,
                           32 * (rows + 0.5f));




    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            // Display Text
            window.clear(sf::Color::Blue);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    window.draw(tiles.at(i).at(j).tileSprite);
                }
            }
            window.draw(happyFaceSprite);
            window.draw(debugSprite);
            window.draw(playSprite);
            window.draw(leaderboardSprite);
            window.display();

        }
    }

}

