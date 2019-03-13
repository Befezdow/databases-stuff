#ifndef CAT_H
#define CAT_H

#include <QString>
#include <QChar>

#define MAX_SIZE_OF_NAME 22                 //размер имени котика из БД
#define MAX_SIZE_OF_BREED 61                //размер породы котика из БД
#define CAT_SIZE 86                         //размер одного котика для записи

class Cat
{
    QString name;                           //имя котика
    QString breed;                          //порода
    unsigned short age;                     //возраст
    QChar gender;                           //пол

public:
//    Cat();
    Cat(QString name="", QString breed="", unsigned short age=0, QChar gender='m');

    friend QDataStream& operator << (QDataStream& stream, Cat &cat);
    friend QDataStream& operator >> (QDataStream& stream, Cat &cat);

    void print() const;                     //напечатать котика

    unsigned short getAge() const   { return age; }
    QString getName() const         { return name; }
    QString getBreed() const        { return breed; }
    QChar getGender() const         { return gender; }

    bool operator == (const Cat &c);
};

#endif // CAT_H
