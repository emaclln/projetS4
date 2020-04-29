#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "structure/graphe.h"

class Interface
{
private :
    int m_indice; //coorespond � la "case" du vecteur pour indiquer sur quel grpahe on travail
    std::vector <Graphe*> m_graphes;
public :
    Interface(int indice);
    Interface();
    void initialisation ();
    void affichageSvg (int selec)const;
    void ajoutGraphe(Graphe* nv);
    void creationGraphe(std::string nomFichier);
    void remplirPoids(std::string nomFichier);
    void remplirFichier(std::string nomFichier);
};


#endif // INTERFACE_H_INCLUDED