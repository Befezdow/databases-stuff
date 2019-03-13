#ifndef NAMEFUNCTOR_H
#define NAMEFUNCTOR_H

#include "functor.h"

class NameLessFunctor : public Functor
{
public:
    NameLessFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getName() < cat2.getName();
    }
};

class BreedLessFunctor : public Functor
{
public:
    BreedLessFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getBreed() < cat2.getBreed();
    }
};

class AgeLessFunctor : public Functor
{
public:
    AgeLessFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getAge() < cat2.getAge();
    }
};

class GenderLessFunctor : public Functor
{
public:
    GenderLessFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getGender() < cat2.getGender();
    }
};

class NameEqualFunctor : public Functor
{
public:
    NameEqualFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getName() == cat2.getName();
    }
};

class BreedEqualFunctor : public Functor
{
public:
    BreedEqualFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getBreed() == cat2.getBreed();
    }
};

class AgeEqualFunctor : public Functor
{
public:
    AgeEqualFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getAge() == cat2.getAge();
    }
};

class GenderEqualFunctor : public Functor
{
public:
    GenderEqualFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getGender() == cat2.getGender();
    }
};

class NameStartsWithFunctor : public Functor
{
public:
    NameStartsWithFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getName().startsWith(cat2.getName());
    }
};

class BreedStartsWithFunctor : public Functor
{
public:
    BreedStartsWithFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return cat1.getBreed().startsWith(cat2.getBreed());
    }
};

class AgeStartsWithFunctor : public Functor
{
public:
    AgeStartsWithFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return QString::number(cat1.getAge()).startsWith(QString::number(cat2.getAge()));
    }
};

class GenderStartsWithFunctor : public Functor
{
public:
    GenderStartsWithFunctor() {}

    virtual bool operator () (const Cat& cat1, const Cat& cat2)
    {
        return QString(cat1.getGender()).startsWith(QString(cat2.getGender()));
    }
};

#endif // NAMEFUNCTOR_H
