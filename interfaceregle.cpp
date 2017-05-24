#include "interfaceregle.h"

InterfaceRegle::InterfaceRegle(QHBoxLayout *p, int v, int taille, Jeu_de_Regle *J, Jeu_de_Regle_nt* J_nt, vector<EtatType *> *tabEtats, QWidget *parent) : QWidget(parent)
{
    couleurs = tabEtats;
    layoutPere = p;
    voisinage = v;
    tailleMatrice = taille;
    Jdr = J;
    Jdr_nt = J_nt;
    saisieDepart = new QComboBox();
    saisieArrive = new QComboBox();
    saisieArriveProba = new QComboBox();
    layoutTabSaisieRegle = new QGridLayout();

    for(unsigned int i = 0; i<tabEtats->size(); i++){
        QColor c = tabEtats->at(i)->GetColor();
        QString n = tabEtats->at(i)->GetNom();
        saisieDepart->addItem(n);
        saisieArrive->addItem(n);
        saisieArriveProba->addItem(n);

        QLineEdit *E = new QLineEdit();
        QString cname = c.name();
        cname.push_front("background-color: ");
        E->setStyleSheet(cname);
        E->setText("  ");
        E->setReadOnly(true);
        layoutTabSaisieRegle->addWidget(E,0,i);
        E->show();
        QLineEdit *F = new QLineEdit();
        tabSaisieRegle.push_back(F);
        layoutTabSaisieRegle->addWidget(F,1,i);
        F->show();

    }


    layoutPrincipal = new  QVBoxLayout(this);

        chargerBouton = new QPushButton("Charger depuis...");
        chargerBouton->show();
        connect(chargerBouton, SIGNAL(clicked(bool)),this,SLOT(ChargerRegles()));
        layoutPrincipal->addWidget(chargerBouton);

        layoutDA = new QHBoxLayout();
        layoutPrincipal->addLayout(layoutDA);

             labelDepart = new QLabel();
             labelDepart->setText("Depart :");
             labelDepart->show();
             layoutDA->addWidget(labelDepart);

             saisieDepart->show();
             layoutDA->addWidget(saisieDepart);

             labelArrive = new QLabel();
             labelArrive->setText("Arrive :");
             labelArrive->show();
             layoutDA->addWidget(labelArrive);

             saisieArrive->show();
             layoutDA->addWidget(saisieArrive);
        layoutProba = new QHBoxLayout();
        layoutPrincipal->addLayout(layoutProba);

            labelProba = new QLabel();
            labelProba->setText("Proba ?");
            labelProba->show();
            layoutProba->addWidget(labelProba);

            checkProba = new QCheckBox();
            checkProba->show();
            connect(checkProba, SIGNAL(stateChanged(int)),this,SLOT(CheckboxStateChanged()));
            layoutProba->addWidget(checkProba);

            saisieProba = new QSpinBox();
            saisieProba->setRange(1,99);
            saisieProba->setDisabled(true);
            layoutProba->addWidget(saisieProba);

            labelArriveP = new QLabel();
            labelArriveP->setText("%    Arrive p-1 :");
            labelArriveP->show();
            layoutProba->addWidget(labelArriveP);

            saisieArriveProba->show();
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

        fenetreRegleScroll->show();

        fenetreRegleScroll->setWidget(fenetreRegle);

        layoutPrincipal->addWidget(fenetreRegleScroll);

        layoutBouton = new QHBoxLayout();
        layoutPrincipal->addLayout(layoutBouton);

            validerBouton = new QPushButton("Valider");
            validerBouton->show();
            connect(validerBouton, SIGNAL(clicked(bool)),this,SLOT(ValiderRegles()));
            layoutBouton->addWidget(validerBouton);

            enregistrerBouton = new QPushButton("Enregistrer sous...");
            enregistrerBouton->show();
            connect(chargerBouton, SIGNAL(clicked(bool)),this,SLOT(EnregistrerRegles()));
            layoutBouton->addWidget(enregistrerBouton);


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
    if(verifRegle()) {
        RegleType *E;
        if (checkProba->checkState() == Qt::Checked)
            {E = new RegleType(&r, saisieDepart->currentIndex(), saisieArrive->currentIndex() , &tabSaisieRegle, saisieProba->value(), saisieArriveProba->currentIndex());}
        else
            { E = new RegleType(&r, saisieDepart->currentIndex(), saisieArrive->currentIndex() , &tabSaisieRegle, 100, saisieArrive->currentIndex());}

        E->show();
        fenetreRegleLayout->addWidget(E);
        r.push_back(E);

        saisieDepart->setCurrentIndex(0);
        saisieArrive->setCurrentIndex(0);
        saisieArriveProba->setCurrentIndex(0);
        saisieProba->setValue(1);
        checkProba->setChecked(false);
        for (unsigned int i = 0; i<tabSaisieRegle.size(); i++){
            tabSaisieRegle.at(i)->setText("");
        }
    }
}

void InterfaceRegle::EnregistrerRegles(){
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier Texte(*.txt *.ol *.fe)");
    QFile file(fichier);
     /*
    // Ouverture en écriture seule et petites optimisations avec QIODevice::Text
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
    // On écrit à l'emplacement du fichier en mettant le contenu de la zone de texte dedans
    file.write(zoneTexte->toPlainText().toAscii());
     */
}

void  InterfaceRegle::ChargerRegles(){

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers Texte (*.txt)");

}

void InterfaceRegle::ValiderRegles()
{
    for(unsigned int i = 0; i<r.size(); i++){
        Jdr_nt->ajout_regle(r.at(i)->getDepart(),r.at(i)->getArrivee(),r.at(i)->getRegle(), r.at(i)->getProba());
    }
    Jdr->set_value(*Jdr_nt);
    delete Jdr_nt;
    saisieDepart->setDisabled(true);
    saisieArriveProba->setDisabled(true);
    saisieArrive->setDisabled(true);
    saisieProba->setDisabled(true);
    checkProba->setDisabled(true);
    ajouterBouton->setDisabled(true);
    fenetreRegle->setDisabled(true);
    validerBouton->setDisabled(true);

    Matrice* matrice = new Matrice(tailleMatrice,(unsigned int)tabSaisieRegle.size());
    matrice->setMoore(!voisinage);
    Iterateur* iterateur = new Iterateur();
    iterateur->setJDR(Jdr);
    InterfaceMatrice* interMatrice = new InterfaceMatrice(matrice,iterateur,couleurs);
    interMatrice->show();
    layoutPere->addWidget(interMatrice);
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
