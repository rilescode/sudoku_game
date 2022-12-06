#include <iostream>
#include "Cell.h"
#include "Board.cpp"

// to compile:
// g++ -Wall -std=c++11 -o Solver Cell.cpp Solver.cpp
// to run:
// ./Solver


//need to look into backtracking algorithm in order to solve this puzzle
int main (int argc, char **argv){
    Cell c1(5);
    Cell c2(10);

    c1.setValue(7);

    int number = 35;


    std::cout << "cellVal " << c1.getValue() << std::endl;
    std::cout << "cellVal " << c2.getValue() << std::endl;

    std::cout << "address of number: " << &number << std::endl;
    Board b1 = Board();

    int boardVals[9][9]= 
    {
        {2, 8, 7, 5, 4, 0, 0, 0, 6},
        {0, 5, 0, 0, 0, 2, 8, 4, 9},
        {0, 6, 0, 0, 3, 0, 0, 7, 0},
        {0, 0, 6, 0, 5, 7, 3, 0, 0},
        {1, 0, 8, 0, 0, 0, 4, 0, 7},
        {0, 7, 3, 0, 0, 0, 9, 6, 1},
        {6, 0, 0, 4, 0, 0, 0, 0, 0},
        {0, 0, 5, 7, 0, 3, 0, 9, 0},
        {7, 0, 0, 9, 2, 0, 0, 1, 5},
    };

    int hardBoardVals[9][9] = 
    {
	{0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 7, 9, 0, 8, 6, 0, 5, 4},
	{0, 0, 0, 0, 0, 7, 0, 0, 6},
	{6, 3, 0, 0, 0, 0, 0, 7, 0},
	{0, 0, 0, 9, 0, 5, 0, 0, 0},
	{0, 8, 0, 0, 0, 0, 0, 2, 5},
	{7, 0, 0, 4, 0, 0, 0, 0, 0},
	{5, 6, 0, 1, 2, 0, 8, 4, 7},
	{1, 0, 0, 0, 0, 0, 0, 0, 0}
};


    //b1.toString();
    for(int i = 0; i < 9; i++){
        for(int j = 0; j<9; j++){
            b1.setCell(i, j, hardBoardVals[i][j]);
        }
    }
    b1.toString();
    b1.solve();
    std::cout << "after solving: " << std::endl; 
    b1.toString();
    
    return 0;

   

}