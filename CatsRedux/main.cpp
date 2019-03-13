#include <QApplication>
#include "maingui.h"

void insertCats(BTree<Cat>& t1, BTree<Cat>& t2, BTree<Cat>& t3, BTree<Cat>& t4)
{
    Cat c1("Pushok","Dikiy",2,'m');
    Cat c2("Murka","Gorodskaya",1,'f');
    Cat c3("Dymka","Britanec",2,'f');
    Cat c4("Persik","Dvoroviy",5,'m');
    Cat c5("Timka","Siam",3,'m');
    Cat c6("Kesha","Pers",6,'m');
    Cat c7("Sam","Dvoroviy",1,'m');
    Cat c8("Belka","Dvoroviy",4,'f');
    Cat c9("Alisa","Siam",8,'f');

    t1.addElement(c1);
    t1.addElement(c2);
    t1.addElement(c3);
    t1.addElement(c4);
    t1.addElement(c5);
    t1.addElement(c6);
    t1.addElement(c7);
    t1.addElement(c8);
    t1.addElement(c9);

    t2.addElement(c1);
    t2.addElement(c2);
    t2.addElement(c3);
    t2.addElement(c4);
    t2.addElement(c5);
    t2.addElement(c6);
    t2.addElement(c7);
    t2.addElement(c8);
    t2.addElement(c9);

    t3.addElement(c1);
    t3.addElement(c2);
    t3.addElement(c3);
    t3.addElement(c4);
    t3.addElement(c5);
    t3.addElement(c6);
    t3.addElement(c7);
    t3.addElement(c8);
    t3.addElement(c9);

    t4.addElement(c1);
    t4.addElement(c2);
    t4.addElement(c3);
    t4.addElement(c4);
    t4.addElement(c5);
    t4.addElement(c6);
    t4.addElement(c7);
    t4.addElement(c8);
    t4.addElement(c9);
}

void printTrees(BTree<Cat>& t1, BTree<Cat>& t2, BTree<Cat>& t3, BTree<Cat>& t4)
{
    QList<Cat> cats = t1.getAll();//tree.getStartsWith(Cat("B",""));//tree.getInRange(Cat("","",1,'m'),Cat("","",5,'m'));

    foreach(Cat c, cats)
    {
        c.print();
    }

    qDebug()<<endl;

    cats = t2.getAll();//tree.getStartsWith(Cat("B",""));//tree.getInRange(Cat("","",1,'m'),Cat("","",5,'m'));

    foreach(Cat c, cats)
    {
        c.print();
    }

    qDebug()<<endl;

    cats = t3.getAll();//tree.getStartsWith(Cat("B",""));//tree.getInRange(Cat("","",1,'m'),Cat("","",5,'m'));

    foreach(Cat c, cats)
    {
        c.print();
    }

    qDebug()<<endl;

    cats = t4.getAll();//tree.getStartsWith(Cat("B",""));//tree.getInRange(Cat("","",1,'m'),Cat("","",5,'m'));

    foreach(Cat c, cats)
    {
        c.print();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainGUI  wgt;
    wgt.show();

    return a.exec();
}
