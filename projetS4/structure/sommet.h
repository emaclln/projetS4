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

    int m_indice;
    int m_marque;
    std::string m_nom;
    Coord m_coord;

    std::vector< std::pair<Sommet*, double >> m_adjacent;

    double m_Cvp;
    double m_Cd;
    double m_Cp;
    double m_Ci;
    double m_N_Cvp;
    double m_N_Cd;
    double m_N_Cp;
    double m_N_Ci;

public :
    Sommet(int indice, std::string nom, Coord mesCoord);
    Sommet (Sommet* mere);
    void set_adjacent(Sommet* nouveau);
    void set_poids(Sommet* extremite, double poids);
    void set_Cvp(double CvpN, double lambda);
    void set_Cp(double cp, int degre);
    void setMarque(int selec);

    void affichageSVG (Svgfile& svgout,int& indice,Coord& milieu, double max,double min, int selec,bool normalise)const;
    void suppAdjacent(Sommet* supprimer);
    void calculCd(int degre);
    void caculCi();
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

};

#endif // SOMMET_H_INCLUDED

