#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "arrete.h"


class Graphe
{
private :
    bool m_orientation;
    int m_ordre;
    int m_taille;

    std::vector<Sommet*> m_sommets;
    std::vector<Arrete*> m_arretes;
public :
    Graphe(std::string nomFichier);//constructeur de graphe

};



#endif // GRAPHE_H_INCLUDED
