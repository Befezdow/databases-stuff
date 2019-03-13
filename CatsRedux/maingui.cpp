#include "maingui.h"

MainGUI::MainGUI(QWidget *parent): QMainWindow(parent)
{
    try
    {
        treeByName = new BTree<Cat>("nameInfo.b");
        treeByBreed = new BTree<Cat>("breedInfo.b");
        treeByAge = new BTree<Cat>("ageInfo.b");
        treeByGender = new BTree<Cat>("genderInfo.b");
    }
    catch(QString str)
    {
        qDebug()<<str;
        qApp->exit(1);
    }

    f00 = new NameLessFunctor;
    f01 = new NameEqualFunctor;
    f02 = new NameStartsWithFunctor;

    f10 = new BreedLessFunctor;
    f11 = new BreedEqualFunctor;
    f12 = new BreedStartsWithFunctor;

    f20 = new AgeLessFunctor;
    f21 = new AgeEqualFunctor;
    f22 = new AgeStartsWithFunctor;

    f30 = new GenderLessFunctor;
    f31 = new GenderEqualFunctor;
    f32 = new GenderStartsWithFunctor;

    treeByName->setFunctors(f00, f01, f02);
    treeByBreed->setFunctors(f10,f11,f12);
    treeByAge->setFunctors(f20,f21,f22);
    treeByGender->setFunctors(f30,f31,f32);

    find = new FindGUI;
    find->setTrees(treeByName, treeByBreed, treeByAge, treeByGender);

    create = new CreateGUI;
    create->setTrees(treeByName, treeByBreed, treeByAge, treeByGender);

    this->setCentralWidget(find);
    this->menuBar()->addAction("Add cat", create, SLOT(show()));
    this->menuBar()->addAction("Exit", this, SLOT(close()));
}

MainGUI::~MainGUI()
{
    delete create;

    delete treeByName;
    delete treeByBreed;
    delete treeByAge;
    delete treeByGender;

    delete f00;
    delete f01;
    delete f02;

    delete f10;
    delete f11;
    delete f12;

    delete f20;
    delete f21;
    delete f22;

    delete f30;
    delete f31;
    delete f32;

    QDir dir(qApp->applicationDirPath());
    dir.cd("dbfiles");
    foreach (QString file,dir.entryList(QDir::Files))
    {
        dir.remove(file);
    }
    dir.cd("..");
    qDebug()<<dir.rmdir("dbfiles");
}
