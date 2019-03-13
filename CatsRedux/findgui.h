#ifndef GUI_H
#define GUI_H

#include <QtWidgets>
#include "btree.h"
#include "cat.h"

class FirstFilter: public QFrame
{
    Q_OBJECT

    QLabel* label;
    QLineEdit* line;

public:
    FirstFilter(QWidget* parent = Q_NULLPTR);
    QString getValue() const;

public slots:
    void setValidator(const QValidator* validator);
    void setMaxLength(int length);
    void clearField();
};

class SecondFilter: public QFrame
{
    Q_OBJECT

    QLabel* firstLabel;
    QLabel* secondLabel;
    QLineEdit* firstLine;
    QLineEdit* secondLine;

public:
    SecondFilter(QWidget* parent = Q_NULLPTR);
    QPair<QString, QString> getValues() const;

public slots:
    void setValidator(const QValidator* validator);
    void setMaxLength(int length);
    void clearFields();
};

class FindGUI: public QFrame
{
    Q_OBJECT

    BTree<Cat>* treeByName;
    BTree<Cat>* treeByBreed;
    BTree<Cat>* treeByAge;
    BTree<Cat>* treeByGender;

    QComboBox* parameters;

    QGroupBox* filters;

    QRadioButton* equalRadio;
    QRadioButton* inRangeRadio;
    QRadioButton* startsWithRadio;

    FirstFilter* filterWidget1;
    SecondFilter* filterWidget2;

    QIntValidator* intValidator;

    QPushButton* button;

    QTableWidget* table;

public:
    FindGUI(QWidget* parent = Q_NULLPTR);

    void setTrees(BTree<Cat>* treeByName, BTree<Cat>* treeByBreed,
                  BTree<Cat>* treeByAge, BTree<Cat>* treeByGender);

private slots:
    void start();

    void clearFilterWidgets();

    void changeValidator(QString str);

    void setFirstWidgetActive();

    void setSecondWidgetActive();
};

#endif // GUI_H
