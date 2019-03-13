# include "cat.h"
#include <QDataStream>
#include <QDebug>

Cat::Cat(QString name, QString breed, unsigned short age, QChar gender):
    name(name),
    breed(breed),
    age(age),
    gender(gender)
{}

void Cat::print() const
{
    qDebug()<<name<<breed<<age<<gender;
}

bool Cat::operator ==(const Cat &c)
{
    return name == c.name && breed == c.breed && age == c.age && gender == c.gender;
}

QDataStream& operator<<(QDataStream &stream, Cat &cat)
{
    stream.writeRawData(cat.name.toStdString().c_str(), MAX_SIZE_OF_NAME);
    stream.writeRawData(cat.breed.toStdString().c_str(), MAX_SIZE_OF_BREED);
    stream.writeRawData((char*)&cat.age, sizeof(unsigned short));
    char c = cat.gender.toLatin1();
    stream.writeRawData(&c,sizeof(char));

    return stream;
}

QDataStream& operator>>(QDataStream &stream, Cat &cat)
{
    char* temp;
    unsigned int bytesCount;

    bytesCount = MAX_SIZE_OF_NAME;
    temp = new char[bytesCount];
    stream.readRawData(temp, bytesCount);
    cat.name = QString(temp).trimmed();
    delete[] temp;

    bytesCount = MAX_SIZE_OF_BREED;
    temp = new char[bytesCount];
    stream.readRawData(temp, bytesCount);
    cat.breed = QString(temp).trimmed();
    delete[] temp;

    bytesCount = sizeof(unsigned short);
    temp = new char[bytesCount];
    stream.readRawData(temp, bytesCount);
    cat.age = *((char*)temp);
    delete[] temp;

    bytesCount = sizeof(char);
    temp = new char[bytesCount];
    stream.readRawData(temp, bytesCount);
    cat.gender = *temp;
    delete[] temp;

    return stream;
}
