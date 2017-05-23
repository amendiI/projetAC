#ifndef MATRICE_H
#define MATRICE_H

#include <QObject>

#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <cell.h>

#define nbDim 2

class Matrice
{
public:
    Matrice();
    ~Matrice();
    Matrice(const unsigned int newSize);
    Matrice(const unsigned int newSize, const unsigned short nbPossibleStates);
    Matrice(const unsigned int newSize, const unsigned short nbPossibleStates, const int initOption);
    void setMoore(const bool isMoore);
    bool isMoore();
    unsigned int getSize();
    unsigned int getNbCells();
    unsigned short getNbPossibleStates();
    unsigned short getVal(int x,int y);
    void setVal(int x,int y,unsigned short newValue);
    unsigned short getTailleEnvironement();
    unsigned short getNbDimensions();
    Cell* getCell(unsigned int x);
    Cell* getCell(unsigned int x,unsigned int y);
    /*temp*/void afficher();
private:
    unsigned short nbDimensions;
    unsigned int size;
    unsigned short nbPS;
    bool typeVoisinage;
    unsigned short getVal(unsigned short nbD,...);
    Cell* getCell(unsigned short nbD,...);
    void setVal(unsigned short newValue,unsigned short nbD,...);
    Cell* cellules; //sizeMax will be reduce to root(dimension) as sizeTotal equals size^dimension
};

#endif // MATRICE_H
