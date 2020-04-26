//
//  arrete.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#ifndef arrete_h
#define arrete_h

#include "sommet.h"

class Arrete
{
    private :
    
    int m_indice;
    float m_poids;
    std::vector<Sommet*> m_extremite; //0 départ, 1 arrivé
    
    public :
    
    Arrete(int indice, float poids, Sommet* un, Sommet* deux);
    
};

#endif /* arrete_hpp */
