#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "cat.h"

class Functor
{
public:
    Functor() {}

    virtual bool operator ()(const Cat& cat1, const Cat& cat2) = 0;

    virtual ~Functor() {}
};

#endif // ABSTRACT_FUNCTOR_H
