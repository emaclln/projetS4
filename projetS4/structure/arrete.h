
#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
//
//  arrete.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright Â© 2020 Charles HAMERY. All rights reserved.
//


#include "sommet.h"

class Arrete
{

private :
    int m_indice;
    float m_poids;
    double m_Ci;
    double m_N_Ci;
    std::vector<Sommet*> m_extremite; //0 départ, 1 arrivé

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

