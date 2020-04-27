#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED

#include "sommet.h"

class Arrete
{
private :
    int m_indice;
    float m_poids;
    std::vector<Sommet*> m_extremite; //0 départ, 1 arrivé
public :
    Arrete(int indice, float poids, Sommet* un, Sommet* deux);
};

#endif // ARRETE_H_INCLUDED
