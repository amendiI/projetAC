#include "interface.h"


Interface::Interface(QWidget *parent) : QWidget(parent)
{
    Jdr_nt = new Jeu_de_Regle_nt();
    Jdr = new Jeu_de_Regle();
    layout = new QVBoxLayout(this);
    Ip = new InterfaceParametre(Jdr,Jdr_nt, layout);
    Ip->show();
    layout->addWidget(Ip);

}

