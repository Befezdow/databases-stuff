#include "findgui.h"

FindGUI::FindGUI(QWidget *parent): QFrame(parent)
{
    QStringList params({"Name", "Breed", "Age", "Gender"});

    parameters = new QComboBox;
    parameters->addItems(params);

    filters = new QGroupBox("Filters");
    equalRadio = new QRadioButton("Equal");
    inRangeRadio = new QRadioButton("In range");
    startsWithRadio = new QRadioButton("Starts with");
    QHBoxLayout* groupLay = new QHBoxLayout;
    groupLay->addWidget(equalRadio);
    groupLay->addWidget(inRangeRadio);
    groupLay->addWidget(startsWithRadio);
    filters->setLayout(groupLay);

    equalRadio->setChecked(true);

    filterWidget1 = new FirstFilter;
    filterWidget2 = new SecondFilter;

    filterWidget2->hide();

    intValidator = new QIntValidator(0, 1000);

    button = new QPushButton("Find");

    table = new QTableWidget(0, 4);
    table->setHorizontalHeaderLabels(params);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(parameters);
    lay->addWidget(filters);
    lay->addWidget(filterWidget1);
    lay->addWidget(filterWidget2);
    lay->addWidget(button);
    lay->addWidget(table);
    this->setLayout(lay);

    connect(parameters, SIGNAL(currentIndexChanged(QString)), this, SLOT(clearFilterWidgets()));
    connect(parameters, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeValidator(QString)));
    connect(equalRadio, SIGNAL(toggled(bool)), this, SLOT(clearFilterWidgets()));
    connect(inRangeRadio, SIGNAL(toggled(bool)), this, SLOT(clearFilterWidgets()));
    connect(startsWithRadio, SIGNAL(toggled(bool)), this, SLOT(clearFilterWidgets()));

    connect(equalRadio, SIGNAL(clicked(bool)), this, SLOT(setFirstWidgetActive()));
    connect(inRangeRadio, SIGNAL(clicked(bool)), this, SLOT(setSecondWidgetActive()));
    connect(startsWithRadio, SIGNAL(clicked(bool)), this, SLOT(setFirstWidgetActive()));

    connect(button, SIGNAL(clicked(bool)), this, SLOT(start()));
}

void FindGUI::start()
{
    if (!treeByName || !treeByBreed || !treeByAge || !treeByGender)
    {
        QMessageBox::critical(this, "Critical error", "Tree has a null pointer");
        qApp->exit(1);
    }

    QList<Cat> catsList;

    QString currentStr = parameters->currentText();

    try
    {
        if (currentStr == "Name")
        {
            if (equalRadio->isChecked() || startsWithRadio->isChecked())
            {
                QString str = filterWidget1->getValue();
                Cat cat(str);

                if (equalRadio->isChecked())
                {
                    catsList = treeByName->getEqual(cat);
                }
                else
                {
                    catsList = treeByName->getStartsWith(cat);
                }
            }
            else
            {
                QPair<QString, QString> pair = filterWidget2->getValues();
                Cat first(pair.first);
                Cat second(pair.second);
                catsList = treeByName->getInRange(first, second);
            }
        }
        else if (currentStr == "Breed")
        {
            if (equalRadio->isChecked() || startsWithRadio->isChecked())
            {
                QString str = filterWidget1->getValue();
                Cat cat("", str);

                if (equalRadio->isChecked())
                {
                    catsList = treeByBreed->getEqual(cat);
                }
                else
                {
                    catsList = treeByBreed->getStartsWith(cat);
                }
            }
            else
            {
                QPair<QString, QString> pair = filterWidget2->getValues();
                Cat first("", pair.first);
                Cat second("", pair.second);
                catsList = treeByBreed->getInRange(first, second);
            }
        }
        else if (currentStr == "Age")
        {
            if (equalRadio->isChecked() || startsWithRadio->isChecked())
            {
                QString str = filterWidget1->getValue();
                Cat cat("", "", str.toInt());

                if (equalRadio->isChecked())
                {
                    catsList = treeByAge->getEqual(cat);
                }
                else
                {
                    catsList = treeByAge->getStartsWith(cat);
                }
            }
            else
            {
                QPair<QString, QString> pair = filterWidget2->getValues();
                Cat first("", "", pair.first.toInt());
                Cat second("", "", pair.second.toInt());
                catsList = treeByAge->getInRange(first, second);
            }
        }
        else
        {
            if (equalRadio->isChecked() || startsWithRadio->isChecked())
            {
                QString str = filterWidget1->getValue();
                Cat cat("", "", 0, str.at(0));

                if (equalRadio->isChecked())
                {
                    catsList = treeByGender->getEqual(cat);
                }
                else
                {
                    catsList = treeByGender->getStartsWith(cat);
                }
            }
            else
            {
                QPair<QString, QString> pair = filterWidget2->getValues();
                Cat first("", "", 0, pair.first.at(0));
                Cat second("", "", 0, pair.second.at(0));
                catsList = treeByGender->getInRange(first, second);
            }
        }
    }
    catch(QString str)
    {
        qDebug()<<str;
        qApp->exit(1);
    }

    table->setRowCount(0);
    foreach (Cat cat, catsList)
    {
        table->insertRow(table->rowCount());
        QTableWidgetItem* item1 = new QTableWidgetItem(cat.getName());
        QTableWidgetItem* item2 = new QTableWidgetItem(cat.getBreed());
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(cat.getAge()));
        QTableWidgetItem* item4 = new QTableWidgetItem(QString(cat.getGender()));
        item1->setFlags(Qt::ItemIsEnabled);
        item2->setFlags(Qt::ItemIsEnabled);
        item3->setFlags(Qt::ItemIsEnabled);
        item4->setFlags(Qt::ItemIsEnabled);
        table->setItem(table->rowCount() - 1, 0, item1);
        table->setItem(table->rowCount() - 1, 1, item2);
        table->setItem(table->rowCount() - 1, 2, item3);
        table->setItem(table->rowCount() - 1, 3, item4);
    }
}

void FindGUI::clearFilterWidgets()
{
    filterWidget1->clearField();
    filterWidget2->clearFields();
}

void FindGUI::changeValidator(QString val)
{
    if (val == "Name")
    {
        filterWidget1->setMaxLength(22);
        filterWidget2->setMaxLength(22);
        filterWidget1->setValidator(Q_NULLPTR);
        filterWidget2->setValidator(Q_NULLPTR);
    }
    else if (val == "Breed")
    {
        filterWidget1->setMaxLength(61);
        filterWidget2->setMaxLength(61);
        filterWidget1->setValidator(Q_NULLPTR);
        filterWidget2->setValidator(Q_NULLPTR);
    }
    else if (val == "Age")
    {
        filterWidget1->setMaxLength(3);
        filterWidget2->setMaxLength(3);
        filterWidget1->setValidator(intValidator);
        filterWidget2->setValidator(intValidator);
    }
    else
    {
        filterWidget1->setMaxLength(1);
        filterWidget2->setMaxLength(1);
        filterWidget1->setValidator(Q_NULLPTR);
        filterWidget2->setValidator(Q_NULLPTR);
    }
}

void FindGUI::setTrees(BTree<Cat> *treeByName, BTree<Cat> *treeByBreed, BTree<Cat> *treeByAge, BTree<Cat> *treeByGender)
{
    this->treeByName = treeByName;
    this->treeByBreed = treeByBreed;
    this->treeByAge = treeByAge;
    this->treeByGender = treeByGender;
}

void FindGUI::setFirstWidgetActive()
{
    filterWidget1->show();
    filterWidget2->hide();
}

void FindGUI::setSecondWidgetActive()
{
    filterWidget1->hide();
    filterWidget2->show();
}

void SecondFilter::setValidator(const QValidator *validator)
{
    firstLine->setValidator(validator);
    secondLine->setValidator(validator);
}

void SecondFilter::setMaxLength(int length)
{
    firstLine->setMaxLength(length);
    secondLine->setMaxLength(length);
}

void SecondFilter::clearFields()
{
    firstLine->clear();
    secondLine->clear();
}

QPair<QString, QString> SecondFilter::getValues() const
{
    QPair<QString, QString> pair;
    pair.first = firstLine->text();
    pair.second = secondLine->text();
    return pair;
}



SecondFilter::SecondFilter(QWidget *parent): QFrame(parent)
{
    firstLabel = new QLabel("Start value:");
    secondLabel = new QLabel("End value:");

    firstLine = new QLineEdit;
    secondLine = new QLineEdit;

    QGridLayout* lay = new QGridLayout;
    lay->addWidget(firstLabel, 0, 0);
    lay->addWidget(secondLabel, 1, 0);
    lay->addWidget(firstLine, 0, 1);
    lay->addWidget(secondLine, 1, 1);
    this->setLayout(lay);
}

void FirstFilter::clearField()
{
    line->clear();
}

void FirstFilter::setValidator(const QValidator *validator)
{
    line->setValidator(validator);
}

void FirstFilter::setMaxLength(int length)
{
    line->setMaxLength(length);
}

QString FirstFilter::getValue() const
{
    return line->text();
}



FirstFilter::FirstFilter(QWidget *parent): QFrame(parent)
{
    label = new QLabel("Value:");
    line = new QLineEdit;

    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(label);
    lay->addWidget(line);
    this->setLayout(lay);
}
