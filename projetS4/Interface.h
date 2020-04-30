#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "structure/graphe.h"

class Interface
{
private :
    int m_indice; //coorespond ‡ la "case" du vecteur pour indiquer sur quel grpahe on travail
    int m_selecSVG; //permet d'afficher des couleurs pour les sommets en fonction des indices de centralités
    std::vector <Graphe*> m_graphes;
public :

    Interface();
    ~Interface();

    void initialisation ();
    void affichageSvg ()const;
    void copieGraphe();
    void remplirPoids(std::string nomFichier);
    void remplirFichier(std::string nomFichier);
    void afficherListeAdjacence()const;
    void afficherConsole()const;
    void suppArrete(std::string& s1,std::string& s2);
    void ajouterArrete(std::string& s1,std::string& s2);
    void afficherCentralite_Normalise(int selec);
    void afficherCentralite_NON_Normalise(int selec);
    void calculCentralite();
    void sauvegarderCentralite(std::string nomFichier);
    void retourEnArriere();
    void setSelecSVG(int selec);
    void setIndice(int indice);

};


#endif // INTERFACE_H_INCLUDED
