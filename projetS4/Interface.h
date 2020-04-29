#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "structure/graphe.h"

class Interface
{
private :
    int m_indice; //coorespond à la "case" du vecteur pour indiquer sur quel grpahe on travail
    int m_selecSVG;
    std::vector <Graphe*> m_graphes;
public :

	Interface();
	~Interface();
	void initialisation ();
    void affichageSvg (int i=-1)const;
    void ajoutGraphe();
    void remplirPoids(std::string nomFichier);
	void remplirFichier(std::string nomFichier);
	void afficherListeAdjacence(int i=-1)const;
	void afficherConsole(int i=-1)const;
	void suppArrete(std::string& s1,std::string& s2,int i=-1);


};


#endif // INTERFACE_H_INCLUDED
