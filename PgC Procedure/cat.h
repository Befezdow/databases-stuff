#ifndef CAT_H
#define CAT_H

#include <string>
#include <iostream>

class Cat {

   std::string name;
   std::string breed;
   unsigned short age;

public:
   Cat(std::string name = "", std::string breed = "", unsigned short age = 0);

   std::string getName() const;
   void setName(const std::string &value);
   std::string getBreed() const;
   void setBreed(const std::string &value);
   unsigned short getAge() const;
   void setAge(unsigned short value);
   void print();

   friend std::ostream &operator << (std::ostream& stream, Cat &data);
   friend std::istream &operator >> (std::istream& stream, Cat &data);
};

std::ostream &operator << (std::ostream& stream, Cat &data);
std::istream &operator >> (std::istream& stream, Cat &data);

#endif // CAT_H
