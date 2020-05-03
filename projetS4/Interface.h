#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "structure/graphe.h"

class Interface
{
private :
    int m_indice; //coorespond à la "case" du vecteur pour indiquer sur quel grpahe on travail
    int m_selecSVG; //permet d'afficher des couleurs pour les sommets en fonction des indices de centralités
    bool m_normaliseSVG; //permet dans l'affichage s'il faut choisir les indices normalisés ou non
    bool m_comparaisonSVG; //permet de savoir si on affiche 1 ou 2 graphes
    int m_indice_comparantSVG; //permet de savoir l'indice du graphe à afficher pour la comparaison
    std::vector <Graphe*> m_graphes; //ensemble des graphes
public :

    Interface();
    ~Interface();

    void initialisation ();
    void affichageSvg ()const;
    void copieGraphe();
    void remplirPoids(std::string nomFichier);
    void ajouterGraphe(std::string nomFichier);
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

    void connexite();

    void setIndice(int indice);
    void setNormaliseSVG(bool normalise);
    void set_indice_comparantSVG(int indice);
    void setComparaisonSVG(bool comparaison);
    int getComparaisonSVG()const;
    bool get_indice_comparantSVG()const;
    int getIndice()const;

    void comparaison(int indice_compare,int selec);
    void comparaisonCvp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
    void comparaisonCd(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
    void comparaisonCp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
    void comparaisonCiSommet(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant);
    void comparaisonCiArrete(std::vector <Arrete*>& actuel,std::vector<Arrete*>& comparant);

    void k_connexite();

};


#endif // INTERFACE_H_INCLUDED
