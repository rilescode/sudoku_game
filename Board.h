#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "Cell.h"


using namespace std;
class Board{
    private:

        // need 2d vector of cells
        vector<vector<Cell>> cells;
        void solveGiven();
        bool solveRecursive(vector<vector<Cell>>);
        //void solveWithBackTracking(int, int, vector<int>);
        vector<int> getPotentialValues(int row, int col);
        vector<int> getSubgridVals(int row, int col);
        vector<int> getRowVals(int row);
        vector<int> getColVals(int col);
        int unsolvedCells;
        
    public:
        Board();
        //Board(int[][]);
        void setCell(int x, int y, int val);
        Cell getCell(int x, int y);
        void solve();
        void toString();

};

#endif