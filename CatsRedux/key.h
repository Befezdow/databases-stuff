#ifndef KEY_H
#define KEY_H

#include <QDataStream>

template <typename T>
struct Key
{
    unsigned long id;
    T value;

    Key() {}

    Key(unsigned int id, T value):
        id(id),
        value(value)
    {}

    bool lessThen(const Key& other, Functor* less, Functor* equal)
    {
        if ((*equal)(this->value, other.value))
        {
            return this->id < other.id;
        }
        else
        {
            return (*less)(this->value, other.value);
        }
    }
};

template <typename T>
QDataStream& operator << (QDataStream &stream, Key<T>& key)
{
    stream.writeRawData((char*)&key.id, sizeof(unsigned long));

    stream << key.value;

    return stream;
}

template <typename T>
QDataStream& operator >> (QDataStream& stream, Key<T>& key)
{
    unsigned int bytesCount = sizeof(unsigned long);
    char* temp = new char[bytesCount];
    stream.readRawData(temp, bytesCount);
    key.id = *((char*)temp);
    delete[] temp;

    stream >> key.value;

    return stream;
}

#endif // KEY_H
