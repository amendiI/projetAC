#include <QFile>
#include <QString>
#include <QTextStream>
#include <QRegExp>

#include "matrice.h"

Matrice* load(Matrice* matrix){
    QString textFichier;
    QFile fichier("input.matrix");
	//TODO le chemin peut etre passé en paramètre pour etre fourni par un explorateur de fichiers
    if(!fichier.open(QIODevice::ReadOnly|QIODevice::Text)) return NULL;
	//le fichier ne s'est pas ouvert
    textFichier=fichier.readAll();
    fichier.close();
    QRegExp rx("^(\\d+);(\\d+);(\\d+);\\{(\\d+)(?:,\\d+)*\\}$");
    if(rx.indexIn(textFichier) != 0) return NULL;
	//mauvaise syntaxe de fichier !
    bool tmpB=true;
    unsigned short tmp, size=rx.cap(3).toUInt(&tmpB,10), nbPS=rx.cap(2).toUShort(&tmpB,10);
    if(!tmpB)return NULL;
	//erreur de conversion
    matrix=new Matrice(size,nbPS);
    textFichier.remove(0,textFichier.indexOf("{"));
    rx.setPattern("(\\d+)");
    unsigned int cmpt=0,stop=matrix->getNbCells();
    int pos=0;
    while((pos=rx.indexIn(textFichier,pos)) != -1 && cmpt<stop){
        tmp=rx.cap(1).toUShort(&tmpB,10);
        if(tmp>=nbPS)return NULL;
		//valeur incorrecte dans le fichier
        matrix->getCell(cmpt)->setValue(tmp);
        pos+=rx.matchedLength();
        cmpt++;
    }
    if(!tmpB)return NULL;
	//erreur de conversion
	return matrix;
}

int record(Matrice* matrix){   //store only one state (etat courrant)
    QString text="";
        text+=QString::number(matrix->getNbDimensions());
        text+=";";
        text+=QString::number(matrix->getNbPossibleStates());
        text+=";";
        text+=QString::number(matrix->getSize());
        text+=";";
    QString chemin("output.matrix");
	//TODO le chemin peut etre passé en paramètre pour etre fourni par un explorateur de fichiers
    QFile fichier(chemin);
    if(!fichier.open(QIODevice::WriteOnly|QIODevice::Text)) return 1;//le fichier ne s'est pas ouvert
    unsigned int i=0;
    text+="{";
    text+=QString::number(matrix->getCell(i)->getValue());
    for(i=1;i<matrix->getNbCells();i++){
        text+=",";
        text+=QString::number(matrix->getCell(i)->getValue());
    }
    text+="}";
    QTextStream flux(&fichier);
    flux << text;
    fichier.close();
    return 0;
}