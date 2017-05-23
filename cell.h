#ifndef CELL_H
#define CELL_H

#include <QObject>

class Matrice;

class Cell
{
public:
    Cell();
    ~Cell();
    unsigned short getValue();
    void setValue(unsigned short newVal);
    //unsigned short* getEnvironment(); // result will need to be free and ceel's order clearly defined switch nbDimension
    //static void setMatrice(Matrice * addrM);
private:
    unsigned short val;
    //static Matrice * matrice;
};

#endif // CELL_H
