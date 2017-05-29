#ifndef MATRICE_H
#define MATRICE_H

#include <QObject>

#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <cell.h>

#define nbDim 2
#define maxTransition 1000

class Matrice
{
public:
	/*- Constructeurs -*/
    Matrice();
    Matrice(const unsigned int newSize, const unsigned short nbPossibleStates);
    Matrice(const unsigned int newSize, const unsigned short nbPossibleStates, const int initOption);
	/*- Destructeur -*/
    ~Matrice();
	/*- Setters -*/
    void setMoore(const bool isMoore);
    void setVal(int x,int y,unsigned short newValue);
	/*- Getters -*/
    bool isMoore();
    unsigned short getNbDimensions();
    unsigned short getNbPossibleStates();
    unsigned int getSize();
    unsigned int getNbCells();
    unsigned short getVal(int x,int y);
    Cell* getCell(unsigned int x);
    Cell* getCell(unsigned int x,unsigned int y);
    unsigned short getTailleEnvironement();
private:
	/*- Attributs -*/
    unsigned short nbDimensions;
    unsigned int size;
    unsigned short nbPS;
    bool typeVoisinage;
    Cell* cellules;
	/*- Setters et Getters pour Matrice à nbDimension != 2 -*/
    void setVal(unsigned short newValue,unsigned short nbD,...);
    unsigned short getVal(unsigned short nbD,...);
    Cell* getCell(unsigned short nbD,...);
};

#endif // MATRICE_H
