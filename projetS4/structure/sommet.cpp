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

void Sommet::affichageSVG (Svgfile& svgout,int& indice, Coord& milieu)const
{
    if (m_coord.getX()==milieu.getX() && m_coord.getY()==milieu.getY() )
    {
        svgout.addDisk(500,400,5,"red");
        svgout.addText(500-5,400-10,m_nom,"red");
    }
    else
    {
        int ecart_x=(milieu.getX()-m_coord.getX())*indice;
        int ecart_y=(milieu.getY()-m_coord.getY())*indice;
        svgout.addDisk(500-ecart_x,400-ecart_y,5,"red");
        svgout.addText(500-ecart_x-5,400-ecart_y-10,m_nom,"red");
    }
}
