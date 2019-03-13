#ifndef CREATEGUI_H
#define CREATEGUI_H

#include <QtWidgets>
#include "btree.h"
#include "cat.h"

class CreateGUI: public QFrame
{
    Q_OBJECT

    BTree<Cat>* treeByName;
    BTree<Cat>* treeByBreed;
    BTree<Cat>* treeByAge;
    BTree<Cat>* treeByGender;

    QLabel* nameLabel;
    QLabel* breedLabel;
    QLabel* ageLabel;
    QLabel* genderLabel;

    QLineEdit* nameField;
    QLineEdit* breedField;
    QSpinBox* ageField;
    QComboBox* genderField;

    QPushButton* button;

public:
    CreateGUI(QWidget* parent = Q_NULLPTR);

    void setTrees(BTree<Cat>* treeByName, BTree<Cat>* treeByBreed,
                  BTree<Cat>* treeByAge, BTree<Cat>* treeByGender);

private slots:
    void add();

};

#endif // CREATEGUI_H
