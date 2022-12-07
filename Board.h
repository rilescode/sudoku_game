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
        bool solveRecursive(vector<vector<Cell>>, int row, int col);
        //void solveWithBackTracking(int, int, vector<int>);
        bool isSafeValue(vector<vector<Cell>> recurseCells, int row, int col, int value);
        vector<int> getPotentialValues(vector<vector<Cell>>, int row, int col);
        vector<int> getSubgridVals(vector<vector<Cell>>, int row, int col);
        vector<int> getRowVals(vector<vector<Cell>>, int row);
        vector<int> getColVals(vector<vector<Cell>>, int col);
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