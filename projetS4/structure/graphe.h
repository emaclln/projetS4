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
        Graphe(std::vector<Sommet*> buffer1,std::vector<Arrete*> buffer2,bool orient,bool ponderation);
        ~Graphe();

        void affichageSvg (int selec,bool normalise) const;
        void remplirPoids(std::string& nomFichier);
        bool suppArrete(std::string& s1, std::string& s2);
        void ajoutArrete(std::string&  extremite_un, std::string& extremite_deux);
        void afficherListeAdjacence()const;
        void afficherConsole()const;
        void afficherCentralite_Normalise(int selec);
        void afficherCentralite_NON_Normalise(int selec);
        void sauvegardeCentralite(std::string& nomFichier);
        void calculCentralite();
        void calculCd();
        void calculCvp();
        void calculCp();
        void caculCi();

        bool connexite();

        int getOrdre()const;
        bool getOrientation()const;
        int getTaille()const;
        bool getPonde()const;

        std::vector <Arrete*> getArretes () const;
        std::vector <Sommet*> getSommets() const;

        std::map<Sommet*, std::pair<Sommet*, int>> disjtra (int premier, int dernier);
};

#endif // GRAPHE_H_INCLUDED

