#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "graphe.h"

class Interface
{
private :
    int m_indice; //coorespond à la "case" du vecteur pour indiquer sur quel grpahe on travail
    std::vector <Graphe*> m_graphes;
public :
    Interface(int indice, std::string nomFichier);
    void affichageSvg ()const;
    void ajoutGraphe(Graphe* nv);
    void remplirPoids(std::string nomFichier);
};


#endif // INTERFACE_H_INCLUDED
