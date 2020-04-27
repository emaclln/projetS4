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

void Arrete::affichageSVG(Svgfile& svgout, int& indice)const
{
    svgout.addLine(m_extremite[0]->getCoords().getX()*indice,m_extremite[0]->getCoords().getY()*indice,
                   m_extremite[1]->getCoords().getX()*indice,m_extremite[1]->getCoords().getY()*indice,"black");
}
