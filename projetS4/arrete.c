//
//  arrete.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "arrete.h"

Arrete::Arrete(int indice, float poids, Sommet* un, Sommet* deux)
{
    m_indice = indice;
    m_poids = poids;
    m_extremite.push_back( un );
    m_extremite.push_back( deux );
}
