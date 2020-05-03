
#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
//
//  arrete.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright ¬© 2020 Charles HAMERY. All rights reserved.
//


#include "sommet.h"

class Arrete
{

private :
    int m_indice;//indice de l'arrête
    float m_poids;//poids de l'arrête
    double m_Ci;//indice normalisé intermédiarité
    double m_N_Ci;//indice non normalisé intermédiarité
    std::vector<Sommet*> m_extremite; //0 dÈpart, 1 arrivÈ

public :
    Arrete(int indice, Sommet* un, Sommet* deux);
    Arrete(int indice, Sommet* un, Sommet* deux, int poids);

    void affichageSVG(Svgfile& svgout,int& indice,Coord& milieu,bool orientation,bool ponderation,int comparaison)const;
    void remplirPoids(int& poids);
    void suppAdjacent();
    void afficherConsole()const;
    void caculCi(double nbre, int degre);


    int getPoids()const;
    int getIndice()const;
    double get_Ci(bool selec);


    bool trouverArrete(std::string& s1, std::string& s2);

    std::vector<Sommet*> getExtremite()const;
};

#endif // ARRETE_H_INCLUDED

