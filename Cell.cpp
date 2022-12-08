#include <iostream>
#include "Cell.h"

Cell::Cell(){
    containsValue = false;
}

Cell::Cell(int value){
    if(value != 0){
        val = value;
        containsValue = true;
    }
    containsValue = false;
}

void Cell::setValue(int value){
    if(value != 0){
        val = value;
        containsValue = true;
    }
}

int Cell::getValue(){
    if(containsValue){
        return val;
    }
    else{
        return 0;
    }
}

bool Cell::hasValue(){
    return containsValue;
}

