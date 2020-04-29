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
    int m_ordre;
    int m_taille;

    std::vector<Sommet*> m_sommets;
    std::vector<Arrete*> m_arretes;

    public :
        Graphe(std::string nomFichier);//constructeur de graphe
        Graphe(std::vector<Sommet*> buffer1,std::vector<Arrete*> buffer2,int orient);
        ~Graphe();
        void affichageSvg () const;
        void remplirPoids(std::string& nomFichier);
        void suppArrete(std::string& s1, std::string& s2);
        void ajoutArrete(int indice, int  extremite_un, int extremite_deux);
        void afficherCentralite();
        int getOrdre()const;
        bool getOrientation()const;
        int getTaille()const;
        void afficherListeAdjacence()const;
        void afficherConsole()const;
        std::vector <Arrete*> getArretes () const;
        std::vector <Sommet*> getSommets() const;



        std::map<Sommet*, std::pair<Sommet*, int>> disjtra (int premier, int dernier);

        void CalculCentralite ();
        void calculCd();
        void calculCvp();
        void calculCp();
        void caculCi();
};


#endif // GRAPHE_H_INCLUDED

