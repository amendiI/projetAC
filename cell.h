#ifndef CELL_H
#define CELL_H

#include <QObject>

class Matrice;

class Cell
{
public:
	/*- Constructeurs -*/
    Cell();
	/*- Destructeur -*/
    ~Cell();
	/*- Setters -*/
    void setValue(unsigned short newVal);
	/*- Getters -*/
    unsigned short getValue();
private:
	/*- Attributs -*/
    unsigned short val;
};



#endif // CELL_H
