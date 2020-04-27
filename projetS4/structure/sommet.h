//
//  sommet.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "coords.h"
#include "../graphisme/svgfile.h"

class Arrete;

class Sommet
{
private :
    int m_indice;
    std::string m_nom;
    Coord m_coord;
    int m_Cvp;
    int m_Cd;
    int m_Cp;
    int m_Ci;
    std::vector<Arrete*> m_adjacent;

public :
    Sommet(int indice, std::string nom, Coord mesCoord);
    Coord getCoords()const;
    std::string getNom()const;
    void affichageSVG (Svgfile& svgout,int& indice)const;

};

#endif // SOMMET_H_INCLUDED

