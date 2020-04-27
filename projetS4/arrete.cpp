#include "arrete.h"

Arrete::Arrete(int indice, float poids, Sommet* un, Sommet* deux)
{
    m_indice = indice;
    m_poids = poids;
    m_extremite.push_back( un );
    m_extremite.push_back( deux );

}
