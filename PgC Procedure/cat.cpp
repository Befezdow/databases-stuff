#include "cat.h"

Cat::Cat(std::string name, std::string breed, unsigned short age) {
    this->name = name;
    this->breed = breed;
    this->age = age;
}

std::string Cat::getName() const
{
    return name;
}

std::string Cat::getBreed() const
{
    return breed;
}

void Cat::setBreed(const std::string &value)
{
    breed = value;
}

unsigned short Cat::getAge() const
{
    return age;
}

void Cat::setAge(unsigned short value)
{
    age = value;
}

void Cat::print() {
    std::cout << name << '\t' << breed << '\t' << age;
}

void Cat::setName(const std::string &value)
{
    name = value;
}

std::istream &operator >>(std::istream &stream, Cat &data) {

    char* temp = new char[64];
    stream.read(temp, 64);
    data.name = std::string(temp);
    delete temp;

    temp = new char[64];
    stream.read(temp, 64);
    data.breed = std::string(temp);
    delete temp;

    temp = new char[2];
    stream.read(temp, 2);
    data.age = *(unsigned short*)temp;
    delete temp;
}

std::ostream &operator <<(std::ostream &stream, Cat &data) {

    const char* temp = data.name.c_str();
    stream.write(temp, 64);

    temp = data.breed.c_str();
    stream.write(temp, 64);

    temp = (char*)&(data.age);
    stream.write(temp, 2);
}
