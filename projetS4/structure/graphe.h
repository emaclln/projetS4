//
//  graphe.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "arrete.h"
#include "compare.h"

class Graphe
{
    private :

    bool m_orientation;
    bool m_ponderation;
    int m_ordre;
    int m_taille;

    std::vector<Sommet*> m_sommets;
    std::vector<Arrete*> m_arretes;

    public :
        Graphe(std::string nomFichier);//constructeur de graphe
        void affichageSvg (int selec) const;
        void remplirPoids(std::string nomFichier);
        void suppArrete(int indice_Arrete);
        void ajoutArrete(int indice, int  extremite_un, int extremite_deux);
        void afficherCentralité_Normalisé(int selec);
        void afficherCentralité_NON_Normalisé(int selec);
        void sauvegardeCentralité(std::string nomFichier);

    
        std::map<Sommet*, std::pair<Sommet*, int>> disjtra (int premier, int dernier);

        void calculCentralité();
        void calculCd();
        void calculCvp();
        void calculCp();
        void caculCi();
};

#endif // GRAPHE_H_INCLUDED

