#include "interface.h"


Interface::Interface(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    Ip = new InterfaceParametre(layout);
    Ip->show();
    layout->addWidget(Ip);
}

