#include "cell.h"

Cell::Cell(){
    val=0;
}

Cell::~Cell(){

}

unsigned short Cell::getValue(){
    return val;
}

void Cell::setValue(unsigned short newVal){
    val=newVal;
}
