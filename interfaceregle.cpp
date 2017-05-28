#include "interfaceregle.h"

InterfaceRegle::InterfaceRegle()
{
    saisieDepart = new QComboBox();
    saisieArrive = new QComboBox();
    saisieArriveProba = new QComboBox();
    layoutTabSaisieRegle = new QGridLayout();


    layoutPrincipal = new  QVBoxLayout(this);


        layoutDA = new QHBoxLayout();
        layoutPrincipal->addLayout(layoutDA);

             labelDepart = new QLabel();
             labelDepart->setText("Depart :");
             layoutDA->addWidget(labelDepart);

             layoutDA->addWidget(saisieDepart);

             labelArrive = new QLabel();
             labelArrive->setText("Arrive :");
             layoutDA->addWidget(labelArrive);

             layoutDA->addWidget(saisieArrive);
        layoutProba = new QHBoxLayout();
        layoutPrincipal->addLayout(layoutProba);

            labelProba = new QLabel();
            labelProba->setText("Proba ?");
            layoutProba->addWidget(labelProba);

            checkProba = new QCheckBox();
            connect(checkProba, SIGNAL(stateChanged(int)),this,SLOT(CheckboxStateChanged()));
            layoutProba->addWidget(checkProba);

            saisieProba = new QSpinBox();
            saisieProba->setRange(1,100);
            saisieProba->setDisabled(true);
            layoutProba->addWidget(saisieProba);

            labelArriveP = new QLabel();
            labelArriveP->setText("%    Arrive p-1 :");
            layoutProba->addWidget(labelArriveP);

            saisieArriveProba->setDisabled(true);
            layoutProba->addWidget(saisieArriveProba);

        layoutTabSaisieRegle->setHorizontalSpacing(0);
        layoutTabSaisieRegle->setVerticalSpacing(0);
        layoutPrincipal->addLayout(layoutTabSaisieRegle);

        ajouterBouton = new QPushButton("Ajouter +");
        connect(ajouterBouton, SIGNAL(clicked(bool)),this,SLOT(ajouterRegle()));
        layoutPrincipal->addWidget(ajouterBouton);

        fenetreRegleScroll = new QScrollArea();

        fenetreRegle = new QFrame();
        fenetreRegleLayout = new QVBoxLayout(fenetreRegle);


        fenetreRegleScroll->move(50,150);
        fenetreRegleScroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn);
        fenetreRegleScroll->setWidgetResizable(true);

        fenetreRegleScroll->setWidget(fenetreRegle);

        layoutPrincipal->addWidget(fenetreRegleScroll);

        layoutBouton = new QHBoxLayout();
        layoutPrincipal->addLayout(layoutBouton);

            validerBouton = new QPushButton("Valider");
            connect(validerBouton, SIGNAL(clicked(bool)),this,SLOT(ValiderRegles()));
            layoutBouton->addWidget(validerBouton);
			griser(true);
}

vector<QLineEdit *> InterfaceRegle::getVectorRegle()
{
    return tabSaisieRegle;
}

void InterfaceRegle::CheckboxStateChanged(){
    if (checkProba->checkState() == Qt::Checked){
        saisieProba->setDisabled(false);
        saisieArriveProba->setDisabled(false);
    }
    else{
        saisieProba->setDisabled(true);
        saisieArriveProba->setDisabled(true);
    }
}

void InterfaceRegle::ajouterRegle()
{
	if (verifRegle()) {
		RegleType *E;
		if (checkProba->checkState() == Qt::Checked)
		{
			E = new RegleType(&r, saisieDepart->currentIndex(), saisieArrive->currentIndex(), &tabSaisieRegle, saisieProba->value(), saisieArriveProba->currentIndex());
		}
		else
		{
			E = new RegleType(&r, saisieDepart->currentIndex(), saisieArrive->currentIndex(), &tabSaisieRegle, 100, saisieArrive->currentIndex());
		}
		QObject::connect(E, SIGNAL(suppr()), this, SLOT(genererJdrnt()));
		E->show();
		fenetreRegleLayout->addWidget(E);
		r.push_back(E);

		saisieDepart->setCurrentIndex(0);
		saisieArrive->setCurrentIndex(0);
		saisieArriveProba->setCurrentIndex(0);
		saisieProba->setValue(1);
		checkProba->setChecked(false);
		for (unsigned int i = 0; i < tabSaisieRegle.size(); i++) {
			tabSaisieRegle.at(i)->setText("");
		}
		genererJdrnt();
	}
}

void InterfaceRegle::genererJdrnt() {
	Jeu_de_Regle_nt *tmp = Jdr_nt;
	Jdr_nt = new Jeu_de_Regle_nt();
	Jdr_nt->set_val(tmp->get_n(),tmp->get_type_voisinage());
	delete tmp;
	for (unsigned int i = 0; i<r.size(); i++) {
		Jdr_nt->ajout_regle(r.at(i)->getDepart(), r.at(i)->getArrivee(), r.at(i)->getRegle(), r.at(i)->getProba());
	}
}

void InterfaceRegle::ValiderRegles()//TODO facultatif
{
    Jdr->set_value(*Jdr_nt);
	emit validerInterR();
}

void InterfaceRegle::griser(bool b) {
	saisieArrive->setDisabled(b);
	saisieDepart->setDisabled(b);
	checkProba->setDisabled(b);
	validerBouton->setDisabled(b);
	ajouterBouton->setDisabled(b);
}

void InterfaceRegle::reinit() 
{
	for (size_t i = 0; i < r.size(); i++)
		r[i]->hide();
	r.clear();
	delete Jdr_nt;
	Jdr_nt = new Jeu_de_Regle_nt();
	
	for (size_t i = 0; i < tabSaisieRegle.size(); i++)
		tabSaisieRegle[i]->hide();
	tabSaisieRegle.clear();

	QLayoutItem* il;
	while ((il = layoutTabSaisieRegle->takeAt(0)) != 0)
	{
			il->widget()->hide();
			il->widget()->close();
			delete il;
	}
}

bool InterfaceRegle::verifRegle() {

    QRegExp rx("[0-9]|[0-9]\\+|[0-9]\\-|[0-9]\\-[0-9]");
    for(unsigned int i = 0; i< tabSaisieRegle.size(); i++){
        if (tabSaisieRegle.at(i)->text() != "") {
            if (!rx.exactMatch(tabSaisieRegle.at(i)->text())) {
                QMessageBox::information(this,tr("Regle"),tr("Erreur :\n La regle n'est pas valide."));
                return false;
            }
        }
    }
    return true;
}


void InterfaceRegle::setTableauEtats(vector<EtatType *> *tabEtats)
{
    for(unsigned int i = 0; i<tabEtats->size(); i++){
        QString n = tabEtats->at(i)->GetNom();
        saisieDepart->addItem(n);
        saisieArrive->addItem(n);
        saisieArriveProba->addItem(n);

        QLineEdit *E = new QLineEdit();
        QString cname = tabEtats->at(i)->GetColor();
        cname.push_front("background-color: ");
        E->setStyleSheet(cname);
        E->setText("");
        E->setReadOnly(true);
        layoutTabSaisieRegle->addWidget(E,0,i);
        E->show();
        QLineEdit *F = new QLineEdit();
        tabSaisieRegle.push_back(F);
        layoutTabSaisieRegle->addWidget(F,1,i);
        F->show();

    }
}

void InterfaceRegle::setJDR(Jeu_de_Regle *Jeu)
{
    if(Jeu == NULL)
        return;
    Jdr = Jeu;
    Jdr_nt = new Jeu_de_Regle_nt();
}

Jeu_de_Regle_nt *InterfaceRegle::getJDR_nt()
{
    return Jdr_nt;
}

int InterfaceRegle::getNbRegles()
{
	return (int)r.size();
}

int InterfaceRegle::getDepartRegle(int i)
{
	return r.at(i)->getDepart();
}

int InterfaceRegle::getArriveeRegle(int i)
{
	return r.at(i)->getArrivee();
}

int InterfaceRegle::getProbaRegle(int i)
{
	return r.at(i)->getProba()[0];
}

int InterfaceRegle::getProbaArriveeRegle(int i)
{
	return r.at(i)->getProba()[1];
}

QString InterfaceRegle::getVoisinage(int i, int j)
{
	return QString::fromStdString(r.at(i)->getRegle()[j]);
}

void InterfaceRegle::ajouterRegleChargement(int d, int a, int p, int ap, vector<QString> regle)
{
	saisieDepart->setCurrentIndex(d);
	saisieArrive->setCurrentIndex(a);
	checkProba->setChecked(true);
	saisieProba->setValue(p);
	saisieArriveProba->setCurrentIndex(ap);
	for (unsigned int i = 0; i < tabSaisieRegle.size(); i++)
	{
		tabSaisieRegle.at(i)->setText(regle.at(i));
	}
	ajouterRegle();
	
}
