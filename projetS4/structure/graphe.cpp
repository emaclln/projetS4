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
            int num1;
            int num2;

            ifs >> indice >> num1 >> num2;

            m_arretes.push_back(new Arrete(indice, m_sommets[num1], m_sommets[num2]));
        }
};


void Graphe::affichageSvg () const
{
    Svgfile svgout;
    svgout.addGrid();
    //cherhons l'indice pour adapté le graphe à la taille de l'écran 1000*800
    int indice=100; // par défaut on le met à 100
    bool stop;
    //on verifie qu'avec cette indice on peut construire tout le grpahe sinon on le réduit
    int max_x=0;
    int temp_x;
    int max_y=0;
    int temp_y;
    //recherche des points extreme du graphe
    do
    {
        stop=true;
        for (auto it : m_sommets)
        {
            temp_x=it->getCoords().getX();
            if (temp_x>max_x)
                max_x=temp_x;

            temp_y=it->getCoords().getY();
            if (temp_y>max_y)
                max_y=temp_y;
        }
        if (max_x*indice>1000 || max_y*indice>800) //depace
        {
            indice=indice/2;
            stop=false; //on revérifie qu'avec cet nouvel indice ce soit bon
        }

    }
    while (!stop);//tant que le grpahe rentre enier


    for (auto it : m_arretes)
        {
            it->affichageSVG(svgout,indice);
        }

    for (auto it : m_sommets)
    {
        it->affichageSVG(svgout,indice);
    }

}

