#include "creategui.h"

CreateGUI::CreateGUI(QWidget *parent): QFrame(parent)
{
    nameLabel = new QLabel("Name:");
    breedLabel = new QLabel("Breed:");
    ageLabel = new QLabel("Age:");
    genderLabel = new QLabel("Gender:");

    nameField = new QLineEdit;
    breedField = new QLineEdit;
    ageField = new QSpinBox;
    genderField = new QComboBox;

    nameField->setMaxLength(22);
    breedField->setMaxLength(61);

    ageField->setRange(0, 1000);

    genderField->addItems(QStringList({"Female", "Male"}));

    button = new QPushButton("Add");

    QGridLayout* lay = new QGridLayout;
    lay->addWidget(nameLabel, 0, 0);
    lay->addWidget(breedLabel, 1, 0);
    lay->addWidget(ageLabel, 2, 0);
    lay->addWidget(genderLabel, 3, 0);
    lay->addWidget(nameField, 0, 1);
    lay->addWidget(breedField, 1, 1);
    lay->addWidget(ageField, 2, 1);
    lay->addWidget(genderField, 3, 1);
    lay->addWidget(button, 4, 0, 2, 1);
    this->setLayout(lay);

    connect(button,SIGNAL(clicked(bool)),this,SLOT(add()));
}

void CreateGUI::setTrees(BTree<Cat> *treeByName, BTree<Cat> *treeByBreed, BTree<Cat> *treeByAge, BTree<Cat> *treeByGender)
{
    this->treeByName = treeByName;
    this->treeByBreed = treeByBreed;
    this->treeByAge = treeByAge;
    this->treeByGender = treeByGender;
}

void CreateGUI::add()
{
    if (!treeByName || !treeByBreed || !treeByAge || !treeByGender)
    {
        QMessageBox::critical(this, "Critical error", "Tree has a null pointer");
        qApp->exit(1);
    }

    QString name = nameField->text();
    QString breed = breedField->text();
    int age = ageField->value();
    QChar gender = genderField->currentText() == "Female" ? 'f' : 'm';

    if (name.isEmpty() || breed.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Fields can't be emply");
        return;
    }

    Cat cat(name, breed, age, gender);

    cat.print();

    try
    {
        treeByName->addElement(cat);
        treeByBreed->addElement(cat);
        treeByAge->addElement(cat);
        treeByGender->addElement(cat);

        treeByName->printTree();
    }
    catch(QString str)
    {
        qDebug()<<str;
        qApp->exit(1);
    }
}
