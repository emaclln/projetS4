#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "structure/graphe.h"

class Interface
{
private :
    int m_indice; //coorespond � la "case" du vecteur pour indiquer sur quel grpahe on travail
    int m_selecSVG; //permet d'afficher des couleurs pour les sommets en fonction des indices de centralit�s
    bool m_normaliseSVG; //permet dans l'affichage s'il faut choisir les indices normalis�s ou non
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
    void setNormaliseSVG(bool normalise);
    int getIndice()const;

    void comparaison(int indice_compare,int selec);
    void comparaisonCvp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
    void comparaisonCd(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
    void comparaisonCp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
    void comparaisonCi(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
};


#endif // INTERFACE_H_INCLUDED
