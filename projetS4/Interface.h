#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "structure/graphe.h"

class Interface
{
private :
    int m_indice; //coorespond à la "case" du vecteur pour indiquer sur quel grpahe on travail
    std::vector <Graphe*> m_graphes;
public :
    Interface(int indice, std::string nomFichier);
	Interface();
	~Interface();
	void initialisation ();
    void affichageSvg ()const;
    void ajoutGraphe();
    void remplirPoids(std::string nomFichier);
	void remplirFichier(std::string nomFichier);
	void afficherListeAdjacence()const;
	void afficherConsole()const;
	void suppArrete(std::string& s1,std::string& s2);

};


#endif // INTERFACE_H_INCLUDED
