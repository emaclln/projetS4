//
//  graphe.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "graphe.h"

Graphe::Graphe(std::string nomFichier )
{
    
    std::ifstream ifs{nomFichier};//lecture du fichier
           if (!ifs)
               throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
           
    ifs >> m_orientation;
    if ( ifs.fail() )
    throw std::runtime_error("Probleme lecture orientation du graphe");
    
    ifs >> m_ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    for (int i=0; i<m_ordre; ++i)
        {
            int indice;
            std::string nom;
            Coord mesCoord;
            int x;
            int y;
            
            ifs >> indice >> nom >> x >> y;
            
            mesCoord.set_coord(x,y);
            
        m_sommets.push_back( new Sommet(indice, nom, mesCoord) );
        }

    ifs >> m_taille;

    for (int i=0; i<m_taille; ++i)
        {
            int indice;
            float poids;
            int num1;
            int num2;
            
            ifs >> indice >> num1 >> num2;
            
            m_arretes.push_back(new Arrete(indice, poids, m_sommets[num1], m_sommets[num2]));
        }
};
