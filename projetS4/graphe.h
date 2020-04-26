//
//  graphe.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#ifndef graphe_h
#define graphe_h

#include "arrete.h"

class Graphe
{
    private :
    
    bool m_orientation;
    int m_ordre;
    int m_taille;
    
    std::vector<Sommet*> m_sommets;
    std::vector<Arrete*> m_arretes;
    
    public :
    
    Graphe(std::string nomFichier);//constructeur de graphe

};

#endif /* graphe_hpp */
