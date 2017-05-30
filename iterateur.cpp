#include "iterateur.h"

Iterateur::Iterateur(){
    matriceCourante=NULL;
    matriceTransition=NULL;
    etatsVoisins=NULL;
    transitionTable=NULL;
    regles=NULL;
    application=0;
}

Iterateur::~Iterateur(){
    free(matriceTransition);
    free(etatsVoisins);
}

void Iterateur::setMatrice(Matrice* addrM){
    if(addrM!=NULL){
        matriceCourante=addrM;
        matriceTransition=new Matrice(matriceCourante->getSize(),matriceCourante->getNbPossibleStates());
        matriceTransition->setMoore(matriceCourante->isMoore());
        etatsVoisins=(unsigned short*)malloc(matriceCourante->getNbPossibleStates() * sizeof(unsigned short));
        int tmp=matriceCourante->isMoore()?10:6;
        voisins=new unsigned short[8];
        transitionTable=new unsigned short*[maxTransition];
        for(int i=0;i<maxTransition;i++)transitionTable[i]=new unsigned short[tmp];
    }
}

void Iterateur::setJDR(Jeu_de_Regle* rules){
    regles=rules;
}

void Iterateur::setApplication(int app)
{
    application=app;
}

int Iterateur::transformMatrice(){
    unsigned int i;
    for(i=0;i<matriceCourante->getNbCells();i++){
        transformCellule(i);
    }
    for(i=0;i<matriceCourante->getNbCells();i++){
        matriceCourante->getCell(i)->setValue(matriceTransition->getCell(i)->getValue());
    }
    return 0;
}

void Iterateur::setTransitions(unsigned short** trans){
    transitionTable=trans;
}

void Iterateur::transformCellule(unsigned int cellule){
    somEnvironment(cellule);

    switch(application){
    case 2://Game of life
        switch(etatsVoisins[1]){
        case 2 : matriceTransition->getCell(cellule)->setValue(matriceCourante->getCell(cellule)->getValue());
            break;
        case 3 : matriceTransition->getCell(cellule)->setValue(1);
            break;
        default: matriceTransition->getCell(cellule)->setValue(0);
        }
        break;
    case 1://Application table de transition (Boucle de Langton)
        applyTransitionTable(cellule);
        break;
    case 3://Propagation feu de foret
        switch(matriceCourante->getCell(cellule)->getValue()){
        case 1: if(etatsVoisins[3]>0)matriceTransition->getCell(cellule)->setValue(2);
            break;
        case 2: matriceTransition->getCell(cellule)->setValue(3);
            break;
        default: matriceTransition->getCell(cellule)->setValue(matriceCourante->getCell(cellule)->getValue());
        }
        break;
    case 4://Propagation virus
        srand((unsigned)time(NULL));
        switch(matriceCourante->getCell(cellule)->getValue()){
        case 1: if(etatsVoisins[2]>0 && rand()%100>/*p1*/70)matriceTransition->getCell(cellule)->setValue(3);
            break;
        case 2: if(rand()%100>/*p2*/60)matriceTransition->getCell(cellule)->setValue(0);
            else matriceTransition->getCell(cellule)->setValue(3);
            break;
        default: matriceTransition->getCell(cellule)->setValue(matriceCourante->getCell(cellule)->getValue());
        }
        break;
    default://Application JDR
        matriceTransition->getCell(cellule)->setValue((unsigned short)regles->applicationJeu(etatsVoisins,(int)matriceCourante->getCell(cellule)->getValue()));
    }
}

void Iterateur::somEnvironment(unsigned int cellule){

    unsigned int a=cellule%matriceCourante->getSize(),
            b=(cellule-a)/(matriceCourante->getSize()),
            /*nbV=matriceCourante->isMoore()?8:4,*/i;
    bool moore=matriceCourante->isMoore();
    for(i=0;i<matriceCourante->getNbPossibleStates();i++)etatsVoisins[i]=0;
    for(i=0;i<8;i++)voisins[i]=0;
    if(a>0){
        voisins[0]=matriceCourante->getVal(a-1,b);
        if(moore){
            if(b>0)     voisins[1]=matriceCourante->getVal(a-1,b-1);
            if(b<matriceCourante->getSize()-1)voisins[7]=matriceCourante->getVal(a-1,b+1);
        }
    }
    if(a<matriceCourante->getSize()-1){
        voisins[4]=matriceCourante->getVal(a+1,b);
        if(moore){
            if(b>0)     voisins[3]=matriceCourante->getVal(a+1,b-1);
            if(b<matriceCourante->getSize()-1)voisins[5]=matriceCourante->getVal(a+1,b+1);
        }
    }
    if(b>0)     voisins[2]=matriceCourante->getVal(a,b-1);
    if(b<matriceCourante->getSize()-1)voisins[6]=matriceCourante->getVal(a,b+1);
    for(i=0;i<8;i++)etatsVoisins[voisins[i]]++;

}

void Iterateur::applyTransitionTable(unsigned int cellNumber){
    unsigned short tmp=matriceCourante->getCell(cellNumber)->getValue();
    int i;
    if(matriceCourante->isMoore()){for(i=0;i<maxTransition;i++)if(
        voisins[0]==transitionTable[i][1] &&
        voisins[1]==transitionTable[i][2] &&
        voisins[2]==transitionTable[i][3] &&
        voisins[3]==transitionTable[i][4] &&
        voisins[4]==transitionTable[i][5] &&
        voisins[5]==transitionTable[i][6] &&
        voisins[6]==transitionTable[i][7] &&
        voisins[7]==transitionTable[i][8] &&
        tmp==transitionTable[i][0])
    matriceTransition->getCell(cellNumber)->setValue(transitionTable[i][9]);}
    else{
        for(i=0;i<maxTransition;i++){
            if(
        voisins[0]==transitionTable[i][1] &&
        voisins[2]==transitionTable[i][2] &&
        voisins[4]==transitionTable[i][3] &&
        voisins[6]==transitionTable[i][4] &&
        tmp==transitionTable[i][0]){
                matriceTransition->getCell(cellNumber)->setValue(transitionTable[i][5]);
            }
        }
    }
}
