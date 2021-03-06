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

    bool m_orientation;//vrai si graphe orienté sinon faux
    bool m_ponderation;//vrai si graphe est pondéré sinon faux
    int m_ordre;//nbre de sommet
    int m_taille;//nbre d'arrête

    std::vector<Sommet*> m_sommets;//liste des sommets
    std::vector<Arrete*> m_arretes;//liste des arrêtes

    public :

        Graphe(std::string nomFichier);//constructeur de graphe
        Graphe(std::vector<Sommet*> buffer1,std::vector<Arrete*> buffer2,bool orient,bool ponderation);
        ~Graphe();

        void affichageSvg (Svgfile& svgout,int selec,bool normalise,int comparaison) const;
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
        void calculCiSommet();
        void calculCiArrete();

        bool connexite();

        int getOrdre()const;
        bool getOrientation()const;
        int getTaille()const;
        bool getPonde()const;

        std::vector <Arrete*> getArretes () const;
        std::vector <Sommet*> getSommets() const;

        std::map<Sommet*, std::pair<Sommet*, int>> disjtra (int premier, int dernier);
        std::map<Sommet*,std::pair<std::vector<Sommet*>, int>> disjtraCi(Sommet* depart);
        std::vector<std::vector<Sommet*>> recurCI(std::map<Sommet*,std::pair<std::vector<Sommet*>, int>> pred, Sommet* selec, Sommet* depart);

        void trouverTTchemins (std::vector<std::vector<Sommet*>>& tt_chemins, std::vector<Sommet*> chemin_divergent,Sommet* selectionne, Sommet* arrive);
        void k_connexite();
};

#endif // GRAPHE_H_INCLUDED

