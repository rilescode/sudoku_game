#include <iostream>
#include "board.h"

using namespace std;
Board::Board(int size): boardSize(size)
{
    // init 2d vector of empty cells
    for (int i = 0; i < boardSize; i++)
    {
        cells.push_back(vector<Cell>());
        for (int j = 0; j < boardSize; j++)
        {
            cells.at(i).push_back(Cell(0));
            unsolvedCells++;
        }
    }
}

// Board::Board(int boardVals[][]){
//     for(int i = 0; i < boardSize; i++){
//         for(int j = 0; j<boardSize; j++){
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
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            std::cout << getCell(i, j).getValue() << " ";
        }
        std::cout << " " << std::endl;
    }
}

void Board::solve()
{
    // first need to input all values that can be solved
    // this operation is faster than recursing
    solveGiven(cells);
    std::cout << "after solving given: \n";
    toString();

    // then need to use backtracking to solve the remaining values
    if(!solveRecursive(cells, 0, 0)){
         cout << "NO SOLUTION" << endl;
    }

}

void Board::solveGiven(vector<vector<Cell>> theCells)
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
        for (int row = 0; row < boardSize; row++)
        {
            for (int col = 0; col < boardSize; col++)
            {
                if (!theCells.at(row).at(col).hasValue())
                {
                    Cell curCell;
                    vector<int> potentialValues = getPotentialValues(theCells, row, col);


                    // if potentials.size = 1
                    if (potentialValues.size() == 1)
                    {
                        theCells.at(row).at(col).setValue(potentialValues[0]);
                        insertedVals = true;
                    }
                }
            }
        }
    }
    cells = theCells;
}


bool Board::solveRecursive(vector<vector<Cell>> recurseCells, int row, int col)
{
    cells = recurseCells;
    //this will print out the whole board
    if (row == boardSize - 1 && col == boardSize){
        return true;

    }

    if(col == boardSize){
        row++;
        col=0;
    }

    //if this cell is already solved, continue
    if(recurseCells.at(row).at(col).getValue()>0){
        return solveRecursive(recurseCells, row, col+1);
    }

    for(int val = 1; val <= boardSize; val++){
        if(isSafeValue(recurseCells, row, col, val)){
            recurseCells.at(row).at(col).setValue(val);

            if(solveRecursive(recurseCells, row, col+1)){
                return true;
            }
        }

    }

    /*
    old code not working:
    vector<int> curPotentials = getPotentialValues(row, col);
    for(int i = 0; i < curPotentials.size(); i++){
        recurseCells.at(row).at(col).setValue(curPotentials.at(i));

        //print out current state of board
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                std::cout << recurseCells.at(i).at(j).getValue() << " ";
            }
            std::cout << " " << std::endl;
        }

        if(solveRecursive(recurseCells, row, col+1)){
            return true;
        }
    }
    */
    return false;


    /*
    This is my old code using a for loop
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
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
            if(row == boardSize - 1 && col == boardSize - 1){
                return true;
            }
        }
    }
    */
    return true;
    // for (val in potentialValues)
    // {
    //     // try the value
    //     // if it doesn't work go back
    // }
}

bool Board::isSafeValue(vector<vector<Cell>> recurseCells, int row, int col, int value){

    vector<int> potentialVals = getPotentialValues(recurseCells, row, col);
    // return whether this value is in the potential values
    return(std::find(potentialVals.begin(), potentialVals.end(), value) != potentialVals.end());
}

vector<int> Board::getPotentialValues(vector<vector<Cell>> theCells, int row, int col){
    // populate rowvals
    vector<int> rowVals = getRowVals(theCells, row);

    // populate colVals
    vector<int> colVals = getColVals(theCells, col);

    // iterate through 3x3 subgrid and populate subgridVals
    vector<int> subgridVals = getSubgridVals(theCells, row, col);

    // now we can make a list of potential values for this cell
    // combine these 3 vectors into a set
    // turn combined vector into set in order to get uyn
    vector<int> combined_values;
    combined_values.reserve( rowVals.size() + colVals.size() + subgridVals.size());
    combined_values.insert(combined_values.end(), rowVals.begin(), rowVals.end());
    combined_values.insert(combined_values.end(), colVals.begin(), colVals.end());
    combined_values.insert(combined_values.end(), subgridVals.begin(), subgridVals.end());

    vector<int> potentialValues;

    // for num 1-boardSize
    for (int num = 1; num < boardSize+1; num++)
    {
        // if !set.contains(num)
        if (find(combined_values.begin(), combined_values.end(), num) == combined_values.end())
        {
            potentialValues.push_back(num);
        }
    }
    return potentialValues;
}

vector<int> Board::getRowVals(vector<vector<Cell>> theCells, int row)
{
    vector<int> rowVals;
    Cell curCell;
    for (int curCol = 0; curCol < boardSize; curCol++)
    {
        curCell = theCells.at(row).at(curCol);
        if (curCell.hasValue())
        {
            rowVals.push_back(curCell.getValue());
        }
    }
    return rowVals;
}

vector<int> Board::getColVals(vector<vector<Cell>> theCells, int col)
{
    vector<int> colVals;
    Cell curCell;
    for (int curRow = 0; curRow < boardSize; curRow++)
    {
        curCell = theCells.at(curRow).at(col);
        if (curCell.hasValue())
        {
            colVals.push_back(curCell.getValue());
        }
    }
    return colVals;
}

vector<int> Board::getSubgridVals(vector<vector<Cell>> theCells, int row, int col)
{
    vector<int> subgridVals;
    Cell curCell;
    int subgridRowVal = row - (row % 3);
    int subgridColVal = col - (col % 3);
    for (int subgridRow = 0; subgridRow < 3; subgridRow++)
    {
        for (int subgridCol = 0; subgridCol < 3; subgridCol++)
        {
            curCell = theCells.at(subgridRowVal + subgridRow).at(subgridColVal + subgridCol);
            if (curCell.hasValue())
            {
                subgridVals.push_back(curCell.getValue());
            }
        }
    }
    return subgridVals;
}
