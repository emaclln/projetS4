#ifndef COMPARE_H_INCLUDED
#define COMPARE_H_INCLUDED

#include "sommet.h"

class CompareSommet
{
public:
    bool operator() (std::pair<Sommet*, int> const & a, std::pair<Sommet*, int> const & b)
    {

        if (a.second > b.second) //compare le poids entre un sommmet initial et celui de deux autres
            return true;
        return false;
    }
};

#endif // COMPARE_H_INCLUDED
