#ifndef CELL_H
#define CELL_H
#include <iostream>


class Cell{
    private:
        int val;
        bool containsValue;
        
    public:
        Cell();
        Cell(int);
        void setValue(int);
        int getValue();
        bool hasValue();
};

#endif