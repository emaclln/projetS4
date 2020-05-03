//
//  sommet.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "coords.h"
#include "../graphisme/svgfile.h"


class Sommet
{
private :

    int m_indice;//indice du sommet
    int m_marque;//permet de faire fonctionner des algo tel que disjrka
    std::string m_nom;//nom du sommet
    Coord m_coord;//coordonnées du sommet

    std::vector< std::pair<Sommet*, double >> m_adjacent;//listes des adjacents

    /*les différents indices possible pour le sommet*/
    double m_Cvp;//normalisé vecteur propre
    double m_Cd;//normalisé degré
    double m_Cp;//normalisé proximité
    double m_Ci;//normalisé intermédiarité
    double m_N_Cvp;// non normalisé
    double m_N_Cd;// non normalisé
    double m_N_Cp;// non normalisé
    double m_N_Ci;// non normalisé

public :
    Sommet(int indice, std::string nom, Coord mesCoord);
    void set_adjacent(Sommet* nouveau);
    void set_poids(Sommet* extremite,double poids);
    void set_Cvp(double CvpN, double lambda);
    void set_Cp(double cp, int degre);
    void setMarque(int selec);

    void affichageSVG (Svgfile& svgout,int& indice,Coord& milieu,double max,double min, int selec,bool normalise,int comparaison)const;
    void suppAdjacent(Sommet* supprimer);
    void calculCd(int degre);
    void caculCi(double nbre,int degre);
    void afficherConsole()const;
    void afficherListeAdjacence()const;

    Coord getCoords()const;
    std::string getNom()const;
    std::vector< std::pair<Sommet*, double >> getAdjacent();
    int getMarque()const;
    int getId()const;
    double get_SommeIndice();
    double get_Cvp(bool selec);
    double get_Cd(bool selec);
    double get_Cp(bool selec);
    double get_Ci(bool selec);

};

#endif // SOMMET_H_INCLUDED

