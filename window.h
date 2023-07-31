#include <fstream>
#include<iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
class Window{
public:
    string name = "";
    float width, height;
    int rows, columns, mines;
    Window();   //Default Constructor
};

class GameWindow : public Window{
    int tileCount = rows * columns;
public:
    void startGame();

};