//
// Created by sanje on 8/1/2023.
//

#include "mine.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

Mine::Mine(int rows, int columns, int numMines) {
    //Generates required number of mines
    srand(static_cast<unsigned>(std::time(nullptr)));
    for(int i = 0; i < numMines ; i++){
        bool next = true;
        while(next){
            int random_number = rand() % (rows * columns) + 1;
//            cout << "Random number : " << random_number << endl;
            if(!(find(mineLocation.begin(), mineLocation.end(), random_number) != mineLocation.end())) {
                mineLocation.push_back(random_number);
                next = false;
            }
        }
        cout << mineLocation.at(i) << endl;
    }

    int counter = 0;
    for (int i = 0; i < rows; i++) {
        vector<bool> row;
        for (int j = 0; j < columns; j++) {
            bool minePresent;

            row.push_back(true);
        }
        mines.push_back(row);
    }

}