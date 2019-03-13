#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets>
#include "findgui.h"
#include "creategui.h"
#include "catfunctors.h"

class MainGUI: public QMainWindow
{
    Q_OBJECT

    BTree<Cat>* treeByName;
    BTree<Cat>* treeByBreed;
    BTree<Cat>* treeByAge;
    BTree<Cat>* treeByGender;

    Functor* f00;
    Functor* f01;
    Functor* f02;

    Functor* f10;
    Functor* f11;
    Functor* f12;

    Functor* f20;
    Functor* f21;
    Functor* f22;

    Functor* f30;
    Functor* f31;
    Functor* f32;

    FindGUI* find;
    CreateGUI* create;

public:
    MainGUI(QWidget* parent = Q_NULLPTR);

    ~MainGUI();
};

#endif // MAINGUI_H
