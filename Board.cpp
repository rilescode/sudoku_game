#include <iostream>
#include "Board.h"

using namespace std;
Board::Board()
{
    // init 2d vector of empty cells
    for (int i = 0; i < 9; i++)
    {
        cells.push_back(vector<Cell>());
        for (int j = 0; j < 9; j++)
        {
            cells.at(i).push_back(Cell(0));
            unsolvedCells++;
        }
    }
}

// Board::Board(int boardVals[][]){
//     for(int i = 0; i < 9; i++){
//         for(int j = 0; j<9; j++){
//             setCell(i, j, boardVals[i][j]);
//         }
//     }
// }

void Board::setCell(int x, int y, int val)
{
    if (val != 0)
    {
        unsolvedCells--;
    }
    else{
        // setting cell to zero
        if(getCell(x, y).getValue() != 0){
            unsolvedCells++;
        }
    }
    cells.at(x).at(y).setValue(val);
    
}

Cell Board::getCell(int x, int y)
{
    return cells.at(x).at(y);
}

void Board::toString()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            std::cout << getCell(i, j).getValue() << " ";
        }
        std::cout << " " << std::endl;
    }
}

void Board::solve()
{
    // first need to input all values that can be solved

    solveGiven();
    
    //vector<vector<int>> recurseCells = cells;
    // then need to use backtracking to solve the remaining values
    if(!solveRecursive(cells)){
        cout << "NO SOLUTION" << endl;
    }

}

void Board::solveGiven()
{
    // while true
    // for each value in the grid
    //  make list of all values in row
    //  make list of all values in col
    //  make list of all values in subgrid
    //  make list of all possible values that is the inverse of the Union(row, col, subgrid)
    // if there is only one possible value, assign this value to the cell at this location
    bool insertedVals = true;
    int loopcount = 0;
    while (insertedVals)
    {
        loopcount++;
        insertedVals = false;
        for (int row = 0; row < 9; row++)
        {
            for (int col = 0; col < 9; col++)
            {
                if (!getCell(row, col).hasValue())
                {
                    Cell curCell;
                    vector<int> potentialValues = getPotentialValues(row, col);


                    // if potentials.size = 1
                    if (potentialValues.size() == 1)
                    {
                        setCell(row, col, potentialValues[0]);
                        insertedVals = true;
                    }
                }
            }
        }
    }
}

bool Board::solveRecursive(vector<vector<Cell>> recurseCells)
{
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(cells.at(row).at(col).getValue() == 0){
                vector<int> curPotentials = getPotentialValues(row, col);
                if(curPotentials.size()>0){
                    for(int i: curPotentials){
                        recurseCells.at(row).at(col).setValue(i);
                        if(solveRecursive(recurseCells)){
                            return true;
                        }
                    }
                }
                else{
                    recurseCells.at(row).at(col).setValue(0);
                    return false;
                }
            }
        }
    }
    return true;
    // for (val in potentialValues)
    // {
    //     // try the value
    //     // if it doesn't work go back
    // }
}

vector<int> Board::getPotentialValues(int row, int col){
    // populate rowvals
    vector<int> rowVals = getRowVals(row);

    // populate colVals
    vector<int> colVals = getColVals(col);

    // iterate through 3x3 subgrid and populate subgridVals
    vector<int> subgridVals = getSubgridVals(row, col);

    // now we can make a list of potential values for this cell
    // combine these 3 vectors into a set
    // turn combined vector into set in order to get uyn
    vector<int> combined_values;
    combined_values.reserve( rowVals.size() + colVals.size() + subgridVals.size());
    combined_values.insert(combined_values.end(), rowVals.begin(), rowVals.end());
    combined_values.insert(combined_values.end(), colVals.begin(), colVals.end());
    combined_values.insert(combined_values.end(), subgridVals.begin(), subgridVals.end());

    vector<int> potentialValues;

    // for num 1-9
    for (int num = 1; num < 10; num++)
    {
        // if !set.contains(num)
        if (find(combined_values.begin(), combined_values.end(), num) == combined_values.end())
        {
            potentialValues.push_back(num);
        }
    }
    return potentialValues;
}

vector<int> Board::getRowVals(int row)
{
    vector<int> rowVals;
    Cell curCell;
    for (int curCol = 0; curCol < 9; curCol++)
    {
        curCell = getCell(row, curCol);
        if (curCell.hasValue())
        {
            rowVals.push_back(curCell.getValue());
        }
    }
    return rowVals;
}

vector<int> Board::getColVals(int col)
{
    vector<int> colVals;
    Cell curCell;
    for (int curRow = 0; curRow < 9; curRow++)
    {
        curCell = getCell(curRow, col);
        if (curCell.hasValue())
        {
            colVals.push_back(curCell.getValue());
        }
    }
    return colVals;
}

vector<int> Board::getSubgridVals(int row, int col)
{
    vector<int> subgridVals;
    Cell curCell;
    int subgridRowVal = row - (row % 3);
    int subgridColVal = col - (col % 3);
    for (int subgridRow = 0; subgridRow < 3; subgridRow++)
    {
        for (int subgridCol = 0; subgridCol < 3; subgridCol++)
        {
            curCell = cells[subgridRowVal + subgridRow][(subgridColVal + subgridCol)];
            if (curCell.hasValue())
            {
                subgridVals.push_back(curCell.getValue());
            }
        }
    }
    return subgridVals;
}