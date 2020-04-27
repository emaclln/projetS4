//
//  sommet.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "sommet.h"

Sommet::Sommet(int indice, std::string nom, Coord mesCoord)
{
    m_indice = indice;
    m_nom = nom;
    m_coord = mesCoord;
}

Coord Sommet::getCoords()const
{
    return m_coord;
}

std::string Sommet::getNom()const
{
    return m_nom;
}

void Sommet::affichageSVG (Svgfile& svgout,int& indice)const
{
    svgout.addDisk(m_coord.getX()*indice,m_coord.getY()*indice,5,"red");
    svgout.addText(m_coord.getX()*indice-5,m_coord.getY()*indice-10,m_nom,"red");
}
