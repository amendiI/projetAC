#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T07:14:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lydia
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    interfaceparametre.cpp \
    etattype.cpp \
    interfaceregle.cpp \
    interface.cpp \
    regletype.cpp \
    Jeu_de_Regle.cpp \
    Jeu_de_Regle_nt.cpp \
    Regle.cpp \
    RegleProba.cpp \
    Regle_nt.cpp \
    cell.cpp \
    interfacematrice.cpp \
    iterateur.cpp \
    matrice.cpp

HEADERS  += mainwindow.h \
    interfaceparametre.h \
    etattype.h \
    interfaceregle.h \
    interface.h \
    regletype.h \
    Jeu_de_Regle.h \
    Jeu_de_Regle_nt.h \
    Regle.h \
    RegleProba.h \
    Regle_nt.h \
    cell.h \
    interfacematrice.h \
    iterateur.h \
    matrice.h

FORMS    += mainwindow.ui
