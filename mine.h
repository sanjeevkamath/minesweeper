#include <iostream>
#include <vector>
using namespace std;

class Mine{
public:
    vector<vector<bool>> mines;
    vector<int> mineLocation;
    Mine(int rows, int columns, int numMines);
};