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
        void affichageSvg () const;
        void remplirPoids(std::string nomFichier);
        void suppArrete(int indice_Arrete);
        void ajoutArrete(int indice, int  extremite_un, int extremite_deux);
        void afficherCentralité();
    
        std::map<Sommet*, std::pair<Sommet*, int>> disjtra (int premier, int dernier);

        void CalculCentralité();
        void calculCd();
        void calculCvp();
        void calculCp();
        void caculCi();
};

/* Classe CompareSommet, classe créé pour priorityqueue, source https://www.journaldev.com/35189/priority-queue-in-c-plus-plus */

class CompareSommet
{
    public:

        bool operator() (std::pair<Sommet*, int> const & a, std::pair<Sommet*, int> const & b)
        {
            if (a.second > b.second) //compare le poids entre un sommmet initial et celui de deux autres
                return true;
            return false;
        }
};


#endif // GRAPHE_H_INCLUDED

