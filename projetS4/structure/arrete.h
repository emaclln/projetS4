
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
    bool m_ponderation; //vrai s'il y a une pondération
    std::vector<Sommet*> m_extremite; //0 départ, 1 arrivé

public :
    Arrete(int indice, Sommet* un, Sommet* deux);
    Arrete (Arrete* mere);
    void affichageSVG(Svgfile& svgout,int& indice,Coord& milieu,bool orientation)const;
    void remplirPoids(int& poids);
    void suppAdjacent();
    int getPoids()const;
    int getIndice()const;
    bool getPonde()const;
    std::vector<Sommet*> getExtremite()const;
    bool trouveeArrete(std::string& s1, std::string& s2);
    void afficherConsole()const;
};

#endif // ARRETE_H_INCLUDED

