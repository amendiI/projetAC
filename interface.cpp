#include "interface.h"

void Interface::Reinitialisation() {
	/*delete Ip;
	delete Jdr_nt;
	delete Jdr;

	Jdr_nt = new Jeu_de_Regle_nt();
	Jdr = new Jeu_de_Regle();
	Ip = new InterfaceParametre(layoutH, Jdr, Jdr_nt, layout);
	Ip->show();
	layout->addWidget(Ip);*/
}

Interface::Interface(QWidget *parent) : QWidget(parent)
{
	reinitBouton = new QPushButton("Reinitialiser");
	QObject::connect(reinitBouton, SIGNAL(clicked()), this, SLOT(Reinitialisation()));
    Jdr_nt = new Jeu_de_Regle_nt();
    Jdr = new Jeu_de_Regle();
    layout = new QVBoxLayout();
    layoutH = new QHBoxLayout(this);
    Ip = new InterfaceParametre(layoutH,Jdr,Jdr_nt, layout);
    Ip->show();
	reinitBouton->show();
	layout->addWidget(reinitBouton);
    layout->addWidget(Ip);
    layoutH->addLayout(layout);
}

