//
// Created by sanjeev on 7/27/2023.
//
#include <fstream>
#include <iostream>
#include <algorithm>
#include "window.h"
#include <vector>
#include <cmath>


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

void Window::setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

GameWindow::GameWindow() {
    remainingMines = mines;


    happyFaceTexture.loadFromFile("files/images/face_happy.png");
    debugTexture.loadFromFile("files/images/debug.png");
    playTexture.loadFromFile("files/images/play.png");
    pauseTexture.loadFromFile("files/images/pause.png");
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    negativeTexture.loadFromFile("files/images/digits.png",sf::IntRect(10 * 21,0,21,32));

    happyFaceSprite.setTexture(happyFaceTexture);
    debugSprite.setTexture(debugTexture);
    playSprite.setTexture(playTexture);
    pauseSprite.setTexture(pauseTexture);
    leaderboardSprite.setTexture(leaderboardTexture);
    negativeSprite.setTexture(negativeTexture);

    updateCounter();
    updateTimer(0);

    tenMinutes.setPosition ((columns*32) - 97, 32*(rows + 0.5f) + 16);
    minutes.setPosition ((columns*32) - 76, 32*(rows + 0.5f) + 16);
    tenSeconds.setPosition((columns * 32) - 54, 32 * (rows + 0.5f) + 16);
    seconds.setPosition((columns * 32) - 33, 32 * (rows + 0.5f) + 16);
    counterHundreds.setPosition (33, 32 * ((rows)+0.5f)+16);
    counterTens.setPosition (54, 32 * ((rows)+0.5f)+16);
    counterOnes.setPosition (75, 32 * ((rows)+0.5f)+16);

    negativeSprite.setPosition(12, 32 * ((rows)+0.5f)+16);
    happyFaceSprite.setPosition((columns / 2.0) * 32 - 32,
                                32 * (rows + 0.5f));
    debugSprite.setPosition((width) - 304,
                            32 * (rows + 0.5f));
    playSprite.setPosition((width) - 240,
                           32 * (rows + 0.5f));
    pauseSprite.setPosition((width) - 240,
                            32 * (rows + 0.5f));
    leaderboardSprite.setPosition((width) - 176,
                                  32 * (rows + 0.5f));



}


void GameWindow::startGame() {

    window.create(sf::VideoMode(width, height), "Minesweeper");
    window.setFramerateLimit(60);

    int counter = 1;

    //Randomly generate required number of mines using mine class
    Mine mineLocations(rows, columns, mines);

    //Initialize + set Mines for all tiles
    for (int i = 0; i < rows; i++) {
        vector<Tile> row;
        for (int j = 0; j < columns; j++) {
            Tile tile(j*32, i*32);
            if (find(mineLocations.mineLocation.begin(), mineLocations.mineLocation.end(), counter) != mineLocations.mineLocation.end()){
                tile.hasMine = true;
            }
            row.push_back(tile);
            counter ++;
        }
        tiles.push_back(row);
    }

    checkAdjacent();




    sf::Clock pauseclock;
    sf::Clock clock;
    sf::Clock leaderboardClock;
    sf::Time pauseTime, totalPauseTime, leaderboardTime, totalLeaderboardTime;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if(happyFaceSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition))
                   && event.mouseButton.button == sf::Mouse::Left){
                    newGame = true;
                    window.close();
                }


                if(leaderboardSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition))
                   && event.mouseButton.button == sf::Mouse::Left){

                    if (pause){
                        LeaderBoardWindow leader;
                    }
                    else{

                        pause = true;
                        leaderboardClock.restart();
                        LeaderBoardWindow leader;
                        leaderboardBool = true;
//                        leaderboardTime = leaderboardClock.getElapsedTime();
//                        pause  = false;
//                        totalLeaderboardTime += leaderboardTime;
                    }

//                    leaderboardBool = false;

                    // //////////////////////////////////////////////////////////////////////
                }


                if(debugSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition))
                   && event.mouseButton.button == sf::Mouse::Left){
                    debug = !debug;
                }

                if(pauseSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition))
                                            && event.mouseButton.button == sf::Mouse::Left){
                    pause = !pause;
                    if(pause)   pauseclock.restart();
                    else    totalPauseTime += pauseTime;
                }
                if(!pause){
                    for(int i = 0; i < rows; i++){
                        for(int j = 0; j< columns; j++){
                            if(tiles.at(i).at(j).tileSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition))){
                                if (event.mouseButton.button == sf::Mouse::Left && tiles.at(i).at(j).hidden){
                                    tiles.at(i).at(j).exposeTile();
                                }

                                else if (event.mouseButton.button == sf::Mouse::Right && tiles.at(i).at(j).hidden) {
                                    tiles.at(i).at(j).markFlag();
                                    //Update Counter accordingly
                                    if(tiles.at(i).at(j).flag)   remainingMines --;
                                    else    remainingMines ++;
                                    updateCounter();

                                }
                            }
                        }
                    }
                }

            }


            pauseTime = pauseclock.getElapsedTime();
            victory = checkVictory();
            if (victory)    cout << "YOU WINNNNN";



            if(leaderboardBool){

                leaderboardTime = leaderboardClock.getElapsedTime();
                pause  = false;
                totalLeaderboardTime += leaderboardTime;

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {

                        tiles.at(i).at(j).reloadTextures();

                    }
                }
                leaderboardBool = false;

            }

        }




        // Display Text
        window.clear(sf::Color::Blue);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if(!leaderboardBool){
                    window.draw(tiles.at(i).at(j).tileSprite);
                    window.draw(tiles.at(i).at(j).numberSprite);

                    if (tiles.at(i).at(j).flag)              window.draw(tiles.at(i).at(j).flagSprite);
                    if(debug && tiles.at(i).at(j).hasMine)   window.draw(tiles.at(i).at(j).mineSprite);
                    if(pause)                                      window.draw(tiles.at(i).at(j).pauseSprite);
                }
                else{
                    for(int i = 0; i < rows; i++){
                        for(int j = 0; j< columns; j++) {
                            window.draw(tiles.at(i).at(j).leaderboardTime);
                        }
                    }
                }


            }
        }

        sf::Time elapsedTime = clock.getElapsedTime() - totalPauseTime - totalLeaderboardTime;

        //cout << elapsedTime.asSeconds() << endl;
        if (!pause)     updateTimer(elapsedTime.asSeconds());
        window.draw(tenMinutes);
        window.draw(minutes);
        window.draw(tenSeconds);
        window.draw(seconds);
        window.draw(happyFaceSprite);
        window.draw(counterHundreds);
        window.draw(counterTens);
        window.draw(counterOnes);
        if(remainingMines < 0)  window.draw(negativeSprite);
        window.draw(debugSprite);
        if(pause)       window.draw(playSprite);
        else            window.draw(pauseSprite);
        window.draw(leaderboardSprite);
        window.display();


    }

    if(newGame){

        GameWindow newGameWindow;
        newGameWindow.name = name;
        newGameWindow.startGame();
    }
}



void GameWindow::updateCounter() {

    digits.setSprite(counterHundreds, abs(int(remainingMines / 100)));
    digits.setSprite(counterTens, abs (int((remainingMines % 100) / 10)));
    digits.setSprite(counterOnes, abs(int(remainingMines % 10)));
}


void GameWindow::updateTimer(int timeSeconds) {

    int minutesTens = timeSeconds / 600;
    int timerMinutes = (timeSeconds % 600) / 60;
    int secondsTens = (timeSeconds % 60) / 10;
    int timerSeconds = (timeSeconds % 10);

    digits.setSprite(tenMinutes, minutesTens);
    digits.setSprite(minutes, timerMinutes);
    digits.setSprite(tenSeconds, secondsTens);
    digits.setSprite(seconds, timerSeconds);


}


void GameWindow::checkAdjacent() {
    //Populate data into vector<Tile*> adjacentTiles
    for(int i = 0; i < rows; i++){
        for(int j = 0; j< columns; j++){

            // Check (i-1, j-1)
            if (i - 1 >= 0 && j - 1 >= 0) {
                tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i-1).at(j-1)));
                if((tiles.at(i-1).at(j-1)).hasMine)       (tiles.at(i).at(j)).neighboringMines ++;
            }

            if (i - 1 >= 0) {
                // Chck (i-1, j)
                tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i-1).at(j)));
                if(tiles.at(i-1).at(j).hasMine)      tiles.at(i).at(j).neighboringMines ++;
            }

            if (i - 1 >= 0 && j + 1 < columns) {
                // Check (i-1, j+1)
                tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i-1).at(j+1)));
                if(tiles.at(i-1).at(j+1).hasMine)      tiles.at(i).at(j).neighboringMines ++;
            }

            if (j - 1 >= 0) {
                // check (i, j-1)
                tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i).at(j-1)));
                if(tiles.at(i).at(j-1).hasMine)      tiles.at(i).at(j).neighboringMines ++;
            }

            if (j + 1 < columns) {
                // check (i, j+1)
                tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i).at(j+1)));
                if(tiles.at(i).at(j+1).hasMine)      tiles.at(i).at(j).neighboringMines ++;
            }

            if (i + 1 < rows && j - 1 >= 0) {
                //Check (i+1, j-1)
                tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i+1).at(j-1)));
                if(tiles.at(i+1).at(j-1).hasMine)      tiles.at(i).at(j).neighboringMines ++;
            }

            if (i + 1 < rows) {
                // check (i+1, j)
                tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i+1).at(j)));
                if(tiles.at(i+1).at(j).hasMine)      tiles.at(i).at(j).neighboringMines ++;
            }

            if (i + 1 < rows && j + 1 < columns) {
                // check (i+1, j+1)
            tiles.at(i).at(j).adjacentTiles.push_back(&(tiles.at(i+1).at(j+1)));
                if(tiles.at(i+1).at(j+1).hasMine)      tiles.at(i).at(j).neighboringMines ++;
            }

            tiles.at(i).at(j).numMinesString = tiles.at(i).at(j).numMinesString + to_string(tiles.at(i).at(j).neighboringMines)
                    + ".png";

//            cout << tiles.at(i).at(j).adjacentTiles.size() << endl;

        }

    }

}


bool GameWindow::checkVictory(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(!tiles.at(i).at(j).flag && tiles.at(i).at(j).hidden){
                return false;
            }

        }
    }
    return true;
}









LeaderBoardWindow::LeaderBoardWindow() {
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    headerText.setFont(font);
    headerText.setString("LEADERBOARD");
    headerText.setFillColor(sf::Color::White);
    headerText.setCharacterSize(20);
    setText(headerText, width/4.0f, height/4.0f -120);
    headerText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    ifstream file("files/leaderboard.txt");
    if(file.is_open()){
        string line;
        while (getline(file, line)) {
            Leaders leader;
            stringstream ss(line);

            // Extracting time and leaderName from the line
            getline(ss, leader.time, ',');
            getline(ss, leader.leaderName, ',');

            rankings.push_back(leader);
        }

        file.close();
    }

    leaderString = "1.\t" + rankings.at(0).time + "\t" + rankings.at(0).leaderName + "\n\n"
            + "2.\t" + rankings.at(1).time + "\t" + rankings.at(1).leaderName + "\n\n"
            + "3.\t" + rankings.at(2).time + "\t" + rankings.at(2).leaderName + "\n\n"
            + "4.\t" + rankings.at(3).time + "\t" + rankings.at(3).leaderName + "\n\n"
            + "5.\t" + rankings.at(4).time + "\t" + rankings.at(4).leaderName;

    bodyText.setFont(font);
    bodyText.setString(leaderString);
    bodyText.setFillColor(sf::Color::White);
    bodyText.setCharacterSize(18);
    setText(bodyText, width/4.0f, height/4.0f + 20);
    bodyText.setStyle(sf::Text::Bold);

    openLeaderBoard();
}

void LeaderBoardWindow::openLeaderBoard() {
    sf::RenderWindow leaderboardWindow(sf::VideoMode(width/2, height/2), "Minesweeper");
    leaderboardWindow.setFramerateLimit(60);

    leaderboardWindow.isOpen();
    while (leaderboardWindow.isOpen()) {
        sf::Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }

        leaderboardWindow.clear(sf::Color::Blue);
        leaderboardWindow.draw(headerText);
        leaderboardWindow.draw(bodyText);
        leaderboardWindow.display();
    }
}
