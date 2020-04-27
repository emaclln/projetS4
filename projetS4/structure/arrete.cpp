//
//  arrete.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "arrete.h"

Arrete::Arrete(int indice, Sommet* un, Sommet* deux)
{
    m_indice = indice;
    m_poids = 0;
    m_extremite.push_back( un );
    m_extremite.push_back( deux );
}

void Arrete::affichageSVG(Svgfile& svgout, int& indice, Coord& milieu)const
{
    if (m_extremite[0]->getCoords().getX()==milieu.getX() && m_extremite[0]->getCoords().getY()==milieu.getY())
    {
        int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
        int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;
        svgout.addLine(500,400,500-ecart_x1,400-ecart_y1,"black");
    }
    else
    {
        if (m_extremite[1]->getCoords().getX()==milieu.getX() && m_extremite[1]->getCoords().getY()==milieu.getY() )
        {
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;
            svgout.addLine(500,400,500-ecart_x0,400-ecart_y0,"black");
        }
        else
        {
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;
            int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
            int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;

            svgout.addLine(500-ecart_x0,400-ecart_y0,500-ecart_x1,400-ecart_y1,"black");
        }

    }
}
