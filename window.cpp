//
// Created by sanjeev on 7/27/2023.
//
#include <fstream>
#include "window.h"


Window::Window(){
    ifstream file("files/board_config.cfg");
    if(file.is_open()){
        // Input number of rows, columns, and mines
         file >> columns >> rows >> mines;
         width = columns * 32;
         height = (rows * 32) + 100;
         cout << "No of Columns: " << columns << endl;
         cout << "No of rows: " << rows << endl;
         cout << "No of mines: " << mines << endl;

    }
    else{
        cout << "Error opening board configuration file." << endl;

    }


}
